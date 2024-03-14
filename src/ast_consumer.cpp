module;
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/Decl.h"
#include "clang/Lex/Preprocessor.h"

#include <filesystem>
#include <string>
export module gencppm:ast_consumer;
import :namespaces;
import :ast_visitor;

using namespace clang;

using namespace gencppm;
static void printNamespace(Namespace const& ns, std::string const& prefix = "")
{
	if (!ns.name.empty())
	{
		llvm::outs() << (ns.isInline ? "inline " : "") << "namespace " << ns.name << " {\n";
	}
	for (Namespace::Child const& child : ns.children)
	{
		auto currentPrefix = prefix.ends_with("::") || ns.name.empty() ? prefix + ns.name : prefix + "::" + ns.name;
		if (auto* child_ns = std::get_if<Namespace>(&child))
		{
			printNamespace(*child_ns, currentPrefix);
		}
		else if (auto* namespace_alias = std::get_if<NamespaceAlias>(&child))
		{
			llvm::outs() << "namespace " << namespace_alias->name << " = " << namespace_alias->aliasedName << ";\n";
		}
		else
		{
			llvm::outs() << "using " << currentPrefix << "::" << std::get<std::string>(child) << ";\n";
		}
	}
	if (!ns.name.empty())
	{
		llvm::outs() << "} // namespace " << ns.name << '\n';
	}
}

export namespace gencppm
{
class MyPPCallbacks : public PPCallbacks
{
public:
	MyPPCallbacks(Configuration const& configuration, FilePathToIncludeNameMap& filePathToIncludeNameMap)
	  : configuration{configuration}, filePathToIncludeNameMap{filePathToIncludeNameMap}
	{
	}

	void InclusionDirective(SourceLocation HashLoc, Token const& IncludeTok, StringRef FileName, bool IsAngled,
	                        CharSourceRange FilenameRange, OptionalFileEntryRef const File, StringRef SearchPath,
	                        StringRef RelativePath, Module const* Imported, SrcMgr::CharacteristicKind FileType) override
	{
		if (!File)
		{
			return;
		}

		auto filePath = std::filesystem::path{std::string{File->getName()}}.lexically_normal();
		if (configuration.HeaderWhitelist.empty() || std::ranges::any_of(configuration.HeaderWhitelist, [&FileName](auto const& header) {
			    return FileName.starts_with(header);
		    }))
		{
			// llvm::errs() << "InclusionDirective: " << FileName << " => " << filePath << '\n';
			filePathToIncludeNameMap[filePath] = FileName;
		}
	}

private:
	Configuration const& configuration;
	FilePathToIncludeNameMap& filePathToIncludeNameMap;
};

class MyASTConsumer : public ASTConsumer
{
public:
	explicit MyASTConsumer(ASTContext* Context, Configuration const& configuration, FilePathToIncludeNameMap const& filePathToIncludeNameMap)
	  : Context(Context), configuration{configuration}, filePathToIncludeNameMap{filePathToIncludeNameMap}
	{
	}

	void HandleTranslationUnit(ASTContext& Context) override
	{
		Namespace globalNamespace{"", {}};
		FindDeclarationsVisitor Visitor(this->Context, configuration, filePathToIncludeNameMap, globalNamespace);
		Visitor.TraverseDecl(Context.getTranslationUnitDecl());

		// Print the global namespace
		llvm::outs() << "export {\n";
		printNamespace(globalNamespace);
		llvm::outs() << "}\n";
	}

private:
	ASTContext* Context;
	Configuration const& configuration;
	FilePathToIncludeNameMap const& filePathToIncludeNameMap;
};
} // namespace gencppm
