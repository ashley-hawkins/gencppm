module;
#include <cstddef>
#include <cstdint>
#include <compare>

#include <filesystem>
#include <algorithm>
#include <vector>
export module gencppm:ast_visitor;
import :namespaces;
import :any_of;

import LLVM.Support;

import clang.Basic;
import clang.AST;
import clang.Frontend;

using namespace clang;

export namespace gencppm
{
struct Configuration
{
	std::vector<std::string> HeaderWhitelist;
	std::vector<std::string> NamespaceWhitelist;
	std::vector<std::string> NamespaceBlacklist;

	std::string ModuleName;
	std::string IncludeName;
};

class FindDeclarationsVisitor : public RecursiveASTVisitor<FindDeclarationsVisitor>
{
public:
	explicit FindDeclarationsVisitor(ASTContext* Context, Configuration const& config, FilePathToIncludeNameMap const& filePathToIncludeNameMap, Namespace& globalNamespace)
	  : Context(Context), configuration{config}, filePathToIncludeNameMap{filePathToIncludeNameMap}, globalNamespace{globalNamespace}
	{
	}

	bool VisitNamedDecl(NamedDecl* Declaration)
	{
		auto declName = Declaration->getDeclName().getAsString();
		auto namespaceName = getNamespaceName(Declaration);

		// if (declName == "vector")
		// {
		// 	llvm::errs() << "Name: " << declName << '\n';
		// 	llvm::errs() << "Location: " << Declaration->getLocation().printToString(Context->getSourceManager()) << '\n';
		// 	llvm::errs() << "Decl: " << Declaration->getDeclKindName() << '\n';
		// 	llvm::errs() << "In Namespace: " << namespaceName << '\n';
		// }

		if (declName == "json" || declName == "basic_json")
		{
			// llvm::errs() << "Name: " << declName << '\n';
			// llvm::errs() << "Location: " << Declaration->getLocation().printToString(Context->getSourceManager()) << '\n';
			// llvm::errs() << "Decl: " << Declaration->getDeclKindName() << '\n';
			// llvm::errs() << "In Namespace: " << getNamespaceName(Declaration) << '\n';
		}
		return true;
	}

#define DEFINE_VISITOR(TYPE)                        \
	bool Visit##TYPE##Decl(TYPE##Decl* Declaration) \
	{                                               \
		return VisitDeclCommon(Declaration);        \
	}
	DEFINE_VISITOR(Function)
	DEFINE_VISITOR(Record)
	DEFINE_VISITOR(Enum)
	DEFINE_VISITOR(Typedef)
	DEFINE_VISITOR(Using)
	DEFINE_VISITOR(TypeAlias)
	DEFINE_VISITOR(Template)
#undef DEFINE_VISITOR
	bool VisitVarDecl(VarDecl* Declaration)
	{
		if (Declaration->isLocalVarDeclOrParm())
			return true;
		return VisitDeclCommon(Declaration);

		return true;
	}

	bool VisitNamespaceAliasDecl(NamespaceAliasDecl* Declaration)
	{
		// llvm::errs() << "NamespaceAliasDecl: " << Declaration->getQualifiedNameAsString() << "\n";
		if (!validateDeclaration(Declaration))
		{
			return true;
		}

		std::string declName = Declaration->getDeclName().getAsString();
		std::string qualifiedAliasedNameStr = getQualifiedAliasedName(Declaration);

		globalNamespace.ensureNamespace(getNamespaceAncestryInfo(Declaration)).addNamespaceAliasToNamespace({declName, qualifiedAliasedNameStr});
		return true;
	}

private:
	ASTContext* Context;
	Configuration const& configuration;
	FilePathToIncludeNameMap const& filePathToIncludeNameMap;
	Namespace& globalNamespace;

	std::string getQualifiedAliasedName(NamespaceAliasDecl* const& Declaration)
	{
		auto qualifiedAliasedName = Declaration->getQualifier();
		std::string qualifiedAliasedNameStr;
		if (qualifiedAliasedName)
		{
			llvm::raw_string_ostream os(qualifiedAliasedNameStr);
			qualifiedAliasedName->print(os, Declaration->getASTContext().getPrintingPolicy());
		}
		qualifiedAliasedNameStr += Declaration->getAliasedNamespace()->getDeclName().getAsString();
		return qualifiedAliasedNameStr;
	}

	std::string getNamespaceName(NamedDecl* Declaration)
	{
		auto context = Declaration->getLexicalDeclContext();
		if (context->isNamespace())
		{
			return dyn_cast<NamespaceDecl>(context)->getQualifiedNameAsString();
		}
		return "";
	}

	std::vector<NamespaceInfo> getNamespaceAncestryInfo(Decl* Declaration)
	{
		std::vector<NamespaceInfo> namespaceInfo;

		auto context = Declaration->getLexicalDeclContext();
		NamespaceDecl* namespaceDecl;
		while ((namespaceDecl = dyn_cast<NamespaceDecl>(context)))
		{
			namespaceInfo.emplace_back(std::string{namespaceDecl->getName()}, namespaceDecl->isInline());
			context = context->getParent();
		}

		return namespaceInfo;
	}

	bool validateDeclaration(NamedDecl* Declaration)
	{
		if (!(isa<UsingDecl>(Declaration) || isa<TypeAliasDecl>(Declaration)) && !Declaration->isExternallyVisible())
		{
			// TODO: Handle variables that are not externally visible but would've been accessible if this were a header file
			return false;
		}
		auto lexContext = Declaration->getLexicalDeclContext();
		auto context = Declaration->getDeclContext();

		auto declName = Declaration->getDeclName();

		if (!declName.isIdentifier())
		{
			return false;
		}

		auto declNameStr = declName.getAsString();
		if (declNameStr.empty())
		{
			return false;
		}

		if (declNameStr.contains("__") || declNameStr.size() > 1 && declNameStr[0] == '_' && std::isupper(declNameStr[1]))
		{
			return false;
		}

		if (!((lexContext->isNamespace() || lexContext->isTranslationUnit()) && (context->isNamespace() || context->isTranslationUnit())))
		{
			return false;
		}

		if ((!context->isNamespace() && !context->isTranslationUnit()))
		{
			return false;
		}
		auto sourceLocation = Declaration->getLocation();

		auto file = Context->getSourceManager().getFileEntryRefForID(Context->getSourceManager().getFileID(sourceLocation));
		if (!file)
		{
			return false;
		}
		auto filePath = std::filesystem::path{std::string{file->getName()}}.lexically_normal();
		if (!filePathToIncludeNameMap.contains(filePath))
		{
			return false;
		}

		auto namespaceName = getNamespaceName(Declaration);

		{
			if (namespaceName.contains("__"))
			{
				return false;
			}

			auto namespace_matches = [&namespaceName](std::string_view name) {
				return namespaceName == name || namespaceName.starts_with(std::string{name} + "::");
			};

			if (!configuration.NamespaceWhitelist.empty() && std::find_if(configuration.NamespaceWhitelist.begin(), configuration.NamespaceWhitelist.end(), namespace_matches) == configuration.NamespaceWhitelist.end())
			{
				return false;
			}

			if (std::find_if(configuration.NamespaceBlacklist.begin(), configuration.NamespaceBlacklist.end(), [&namespaceName](std::string const& prefix) {
				    return namespaceName == prefix || namespaceName.starts_with(prefix + "::");
			    }) != configuration.NamespaceBlacklist.end())
			{
				return false;
			}
		}

		if (context->isTranslationUnit())
		{
			if ((declNameStr.length() > 1 && declNameStr[0] == '_' && std::isupper(declNameStr[1])) || declNameStr.contains("__"))
			{
				return false;
			}
		}

		return true;
	}

	bool VisitDeclCommon(NamedDecl* Declaration)
	{
		auto declName = Declaration->getDeclName().getAsString();
		auto namespaceName = getNamespaceName(Declaration);
		// if (declName == "vector")
		// {
		// 	llvm::errs() << "Common visited Name: " << declName << '\n';
		// 	llvm::errs() << "Location: " << Declaration->getLocation().printToString(Context->getSourceManager()) << '\n';
		// 	llvm::errs() << "Decl: " << Declaration->getDeclKindName() << '\n';
		// 	llvm::errs() << "In Namespace: " << namespaceName << '\n';
		// }

		if (!validateDeclaration(Declaration))
		{
			return true;
		}

		// std::string declName = Declaration->getDeclName().getAsString();

		globalNamespace.ensureNamespace(getNamespaceAncestryInfo(Declaration)).addUsingDeclToNamespace(declName);
		return true;
	}
};
} // namespace gencppm
