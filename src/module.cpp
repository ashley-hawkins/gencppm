/*
 * SPDX-FileCopyrightText: © 2024 Ashley Hawkins <awhawkins@proton.me>
 * SPDX-FileContributor: Ashley Hawkins <awhawkins@proton.me>
 *
 * SPDX-License-Identifier: AGPL-3.0-only
 */

module;
#include "includefirst.hpp"

#include <llvm/ADT/StringRef.h>
#include <llvm/Support/Casting.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/raw_ostream.h>

#include <clang/AST/ASTConsumer.h>
#include <clang/AST/ASTContext.h>
#include <clang/Basic/LLVM.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Lex/Preprocessor.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
export module gencppm;
import :namespaces;
import :ast_visitor;
import :ast_consumer;

export namespace gencppm
{
int main(int argc, char const** argv);
}

using namespace clang;
using namespace clang::tooling;

namespace gencppm
{
class GenerateCppmAction : public ASTFrontendAction
{
public:
	GenerateCppmAction(Configuration const& configuration)
	  : configuration(configuration)
	{
	}

	std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance& CI,
	                                               StringRef file) override
	{
		// Print include paths
		// auto& hsOpts = CI.getHeaderSearchOpts();
		// llvm::errs() << "Include paths:\n";
		// llvm::errs() << hsOpts.Sysroot << "\n";
		// for(auto& path : hsOpts.UserEntries)
		// {
		// 	llvm::errs() << path.Path << "\n";
		// }
		// for (auto& path : hsOpts.SystemHeaderPrefixes)
		// {
		// 	llvm::errs() << path.Prefix << "\n";
		// }

		llvm::outs() << "module;\n";
		llvm::outs() << "#include " << "\"" << configuration.IncludeName << "\"" << "\n";
		llvm::outs() << "export module " << configuration.ModuleName << ";\n\n";
		return std::make_unique<MyASTConsumer>(&CI.getASTContext(), configuration, filePathToIncludeNameMap);
	}

	// add pp callbacks
	bool BeginSourceFileAction(CompilerInstance& CI) override
	{
		auto& pp = CI.getPreprocessor();
		filePathToIncludeNameMap.clear();
		pp.addPPCallbacks(std::make_unique<MyPPCallbacks>(configuration, filePathToIncludeNameMap, pp.getSourceManager()));
		return true;
	}

private:
	Configuration const& configuration;
	FilePathToIncludeNameMap filePathToIncludeNameMap;
};

auto myFrontendActionFactory(Configuration const& configuration)
{
	class MyFrontendActionFactory : public FrontendActionFactory
	{
	public:
		MyFrontendActionFactory(Configuration const& configuration)
		  : configuration(configuration)
		{
		}
		std::unique_ptr<FrontendAction> create() override
		{
			return std::make_unique<GenerateCppmAction>(configuration);
		}

	private:
		Configuration const& configuration;
	};

	return std::make_unique<MyFrontendActionFactory>(configuration);
}

int main(int argc, char const** argv)
{
	llvm::cl::OptionCategory GencppmOpts("gencppm options", "Generate .cppms to export symbols of legacy header based libraries.");
	llvm::cl::list<std::string> HeaderWhitelist("H", llvm::cl::desc("List of header prefixes to include in the output. If empty, all are included."), llvm::cl::cat(GencppmOpts));
	llvm::cl::list<std::string> NamespaceWhitelist("w", llvm::cl::desc("List of namespaces to include in the output. If empty, all namespaces are included."), llvm::cl::cat(GencppmOpts));
	llvm::cl::list<std::string> NamespaceBlacklist("b", llvm::cl::desc("If the whitelist is empty, all namespaces are included except those in the blacklist."), llvm::cl::cat(GencppmOpts));

	llvm::cl::opt<std::string> ModuleName("M", llvm::cl::desc("Name of generated module"), llvm::cl::cat(GencppmOpts), llvm::cl::Required);
	llvm::cl::opt<std::string> IncludeName("I", llvm::cl::desc("Relative path of header to #include into the generated module"), llvm::cl::cat(GencppmOpts), llvm::cl::init("module_include.h"));
	auto ExpectedParser = CommonOptionsParser::create(argc, argv, GencppmOpts);
	if (!ExpectedParser)
	{
		// Handle error
		return 1;
	}

	ClangTool Tool(ExpectedParser->getCompilations(),
	               ExpectedParser->getSourcePathList());
	Tool.appendArgumentsAdjuster([](CommandLineArguments args, StringRef filename) {
		args.push_back("-Xclang");
		args.push_back("-internal-isystem");
		args.push_back("-Xclang");
		args.push_back(CLANG_DIR "/include");
		return args;
	});

	return Tool.run(myFrontendActionFactory(Configuration{std::move(HeaderWhitelist), std::move(NamespaceWhitelist), std::move(NamespaceBlacklist), std::move(ModuleName), std::move(IncludeName)}).get());
}
} // namespace gencppm

#if defined(__GLIBCXX__)
// https://github.com/alibaba/async_simple/blob/d6f201192bb332fc9dabcfdf3fa29e85c83c7f45/third_party_module/stdmodules/string.cppm#L28C1-L42C7
// Thank you, Chuanqi Xu, for finding the solution to this problem.
extern "C++"
{
	template class std::allocator<char>;
	template class std::allocator<wchar_t>;
}
#endif
