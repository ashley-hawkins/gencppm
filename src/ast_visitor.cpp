/*
 * SPDX-FileCopyrightText: © 2024 Ashley Hawkins <awhawkins@proton.me>
 * SPDX-FileContributor: Ashley Hawkins <awhawkins@proton.me>
 *
 * SPDX-License-Identifier: AGPL-3.0-only
 */

module;
#include "includefirst.hpp"

#include <algorithm>
#include <filesystem>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

#include <llvm/Support/Casting.h>
#include <llvm/Support/raw_ostream.h>

#include <clang/AST/ASTContext.h>
#include <clang/AST/Decl.h>
#include <clang/AST/DeclBase.h>
#include <clang/AST/DeclCXX.h>
#include <clang/AST/DeclTemplate.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/LLVM.h>
#include <clang/Basic/SourceManager.h>

export module gencppm:ast_visitor;
import :namespaces;
import :any_of;

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
#undef DEFINE_VISITOR
	bool VisitVarDecl(VarDecl* Declaration)
	{
		if (Declaration->isLocalVarDeclOrParm() || Declaration->isTemplateParameter())
			return true;
		return VisitDeclCommon(Declaration);

		return true;
	}

	bool VisitTemplateDecl(TemplateDecl* Declaration)
	{
		if (isa<TemplateTemplateParmDecl>(Declaration))
			return true;
		return VisitDeclCommon(Declaration);
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
		auto context = Declaration->getDeclContext();
		if (context->isNamespace())
		{
			return dyn_cast<NamespaceDecl>(context)->getQualifiedNameAsString();
		}
		return "";
	}

	std::vector<NamespaceInfo> getNamespaceAncestryInfo(Decl* Declaration)
	{
		std::vector<NamespaceInfo> namespaceInfo;

		auto context = Declaration->getDeclContext();
		NamespaceDecl* namespaceDecl;
		while ((namespaceDecl = dyn_cast<NamespaceDecl>(context)))
		{
			namespaceInfo.emplace_back(std::string{namespaceDecl->getName()}, namespaceDecl->isInline());
			context = context->getParent();
		}

		return namespaceInfo;
	}

	static bool isUnreservedName(std::string_view name, bool inGlobalNamespace)
	{
		if (name.empty())
		{
			return false;
		}

		if (inGlobalNamespace && name.front() == '_')
		{
			return false;
		}

		if (!inGlobalNamespace && name.length() > 1 && name.front() == '_' && std::isupper(name[1]))
		{
			return false;
		}

		if (name.contains("__"))
		{
			return false;
		}

		return true;
	}

	bool validateDeclaration(NamedDecl* Declaration)
	{
		constexpr bool allowReservedNames = true;
		if (!isany<UsingDecl, TypeAliasDecl, TypedefDecl, NamespaceAliasDecl>(Declaration) && !Declaration->isExternallyVisible())
		{
			// TODO: Handle variables that are not externally visible but would've been accessible if this were a header file
			return false;
		}
		auto lexContext = Declaration->getLexicalDeclContext();
		auto context = Declaration->getDeclContext();

		auto declName = Declaration->getDeclName();

		if (!declName.isIdentifier() && declName.getCXXOverloadedOperator() == OO_None)
		{
			return false;
		}

		auto declNameStr = declName.getAsString();
		if (declNameStr.empty())
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

		auto file = [location = Declaration->getLocation(), &sourceManager = Context->getSourceManager()] -> OptionalFileEntryRef {
			if (!location.isValid())
			{
				return std::nullopt;
			}

			if (location.isMacroID())
			{
				auto presumedLocation = sourceManager.getPresumedLoc(location);
				if (!presumedLocation.isValid())
				{
					return std::nullopt;
				}
				auto id = presumedLocation.getFileID();
				if (!id.isValid())
				{
					return std::nullopt;
				}
				return sourceManager.getFileEntryRefForID(id);
			}

			auto id = sourceManager.getFileID(location);
			if (!id.isValid())
			{
				return std::nullopt;
			}
			return sourceManager.getFileEntryRefForID(id);
		}();

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
			if (!allowReservedNames)
			{
				std::vector<NamespaceInfo> namespaceInfo = getNamespaceAncestryInfo(Declaration);
				if (!namespaceInfo.empty() && !isUnreservedName(namespaceInfo.back().name, true))
				{
					return false;
				}
				for (auto const& ns : namespaceInfo | std::views::reverse | std::views::drop(1))
				{
					if (!isUnreservedName(ns.name, false))
					{
						return false;
					}
				}
			}
			// Predicate to check if namespaceName is the given namespace or a sub-namespace
			auto namespace_matches = [&namespaceName](std::string_view prefix) {
				return namespaceName == prefix || namespaceName.starts_with(std::string{prefix} + "::");
			};

			// If the whitelist is not empty, and the namespace is not in the whitelist, this is not valid
			if (!configuration.NamespaceWhitelist.empty() && std::find_if(configuration.NamespaceWhitelist.begin(), configuration.NamespaceWhitelist.end(), namespace_matches) == configuration.NamespaceWhitelist.end())
			{
				return false;
			}

			// If the blacklist is not empty, and the namespace is in the blacklist, this is not valid
			if (std::find_if(configuration.NamespaceBlacklist.begin(), configuration.NamespaceBlacklist.end(), namespace_matches) != configuration.NamespaceBlacklist.end())
			{
				return false;
			}
		}

		if (!allowReservedNames && !isUnreservedName(declNameStr, context->isTranslationUnit()))
		{
			return false;
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
