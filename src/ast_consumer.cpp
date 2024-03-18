module;
#include <cstddef>
#include <cstdint>
#include <compare>

#include <algorithm>
#include <filesystem>
#include <string>
export module gencppm:ast_consumer;
import :namespaces;
import :ast_visitor;

import LLVM.Support;

import clang.AST;
import clang.Basic;
import clang.Frontend;
import clang.Tooling;
import clang.Lex;

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
	MyPPCallbacks(Configuration const& configuration, FilePathToIncludeNameMap& filePathToIncludeNameMap, SourceManager& sourceManager)
	  : configuration{configuration}, filePathToIncludeNameMap{filePathToIncludeNameMap}, sourceManager{sourceManager}
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

		auto filePath{std::filesystem::path{std::string{File->getName()}}.lexically_normal()};

		FileEntryRef includedFromFile{*sourceManager.getFileEntryRefForID(sourceManager.getFileID(HashLoc))};
		StringRef includedFromPath{includedFromFile.getName()};
		auto includedFromDir{std::filesystem::path{std::string{includedFromFile.getDir().getName()}}.lexically_normal()};
		auto searchDir{std::filesystem::path{std::string{SearchPath}}.lexically_normal()};

		std::string NormalisedFileName = FileName.str();

		if (!IsAngled && searchDir == includedFromDir)
		{
			llvm::errs() << "Looks like a local include: " << FileName << " => " << filePath << '\n';
			auto mappedPair = filePathToIncludeNameMap.find(std::string{includedFromPath});
			if (mappedPair != filePathToIncludeNameMap.end())
			{
				std::string_view includedFromName = mappedPair->second;
				std::size_t idx{includedFromName.rfind("/")};
				std::string_view dirName = includedFromName.substr(0, std::min(idx + 1, includedFromName.size()));
				NormalisedFileName = std::filesystem::path{std::string{dirName} + RelativePath.str()}.lexically_normal().string();
				llvm::errs() << "Wants local include: \"" << FileName << "\" => <" << NormalisedFileName << "> => " << filePath << '\n';
			}
		}

		if (configuration.HeaderWhitelist.empty() || std::ranges::any_of(configuration.HeaderWhitelist, [&NormalisedFileName](auto const& header) {
			    return NormalisedFileName.starts_with(header);
		    }))
		{
			llvm::errs() << "InclusionDirective: " << (IsAngled ? "<" : "\"") << FileName << (IsAngled ? ">" : "\"");
			if (!IsAngled)
			{
				llvm::errs() << " => <" << NormalisedFileName << ">";
			}
			llvm::errs() << " => " << filePath << '\n';
			filePathToIncludeNameMap[filePath] = NormalisedFileName;
		}
	}

private:
	Configuration const& configuration;
	FilePathToIncludeNameMap& filePathToIncludeNameMap;
	SourceManager& sourceManager;
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
