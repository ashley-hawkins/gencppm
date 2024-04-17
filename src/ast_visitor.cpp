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

	std::vector<NamespaceInfo> getNamespaceAncestryInfo(DeclContext* context)
	{
		std::vector<NamespaceInfo> namespaceInfo;

		NamespaceDecl* namespaceDecl;
		while ((namespaceDecl = dyn_cast<NamespaceDecl>(context)))
		{
			namespaceInfo.emplace_back(std::string{namespaceDecl->getName()}, namespaceDecl->isInline());
			context = context->getParent();
		}

		return namespaceInfo;
	}

	std::vector<NamespaceInfo> getNamespaceAncestryInfo(Decl* Declaration)
	{
		return getNamespaceAncestryInfo(Declaration->getDeclContext());
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

	bool resolveVisibility(NamedDecl* Declaration)
	{
		if (Declaration->isExternallyVisible())
		{
			return true;
		}
		if (isany<TypeAliasDecl, TypedefDecl, NamespaceAliasDecl>(Declaration))
		{
			return true;
		}
		if (auto* usingDecl = dyn_cast<UsingDecl>(Declaration); usingDecl)
		{
			for (auto decl : usingDecl->shadows())
			{
				if (!resolveVisibility(decl->getTargetDecl()))
				{
					return false;
				}
			}
			return true;
		}
		return false;
	}

	bool validateDeclaration(NamedDecl* Declaration)
	{
		constexpr auto debug_on_name = "uint8_t";
		constexpr bool allowReservedNames = true;

		auto lexContext = Declaration->getLexicalDeclContext();
		auto context = Declaration->getDeclContext();
		if (context->isExternCContext())
		{
			context = context->getParent();
		}
		if (lexContext->isExternCContext())
		{
			lexContext = lexContext->getParent();
		}

		if (!resolveVisibility(Declaration))
		{
			return false;
		}

		auto log = [this, &Declaration, context, lexContext](std::string_view message) {
			if (Declaration->getDeclName().getAsString() == debug_on_name)
			{
				llvm::errs() << "Invalid declaration: " << message << '\n';
				llvm::errs() << "Name: " << Declaration->getDeclName().getAsString() << '\n';
				llvm::errs() << "Location: " << Declaration->getLocation().printToString(Context->getSourceManager()) << '\n';
				llvm::errs() << "Decl: " << Declaration->getDeclKindName() << '\n';
				llvm::errs() << "In Namespace: " << getNamespaceName(Declaration) << '\n';
				llvm::errs() << "Context: " << context->getDeclKindName() << '\n';
				llvm::errs() << "LexContext: " << lexContext->getDeclKindName() << '\n';
			}
		};

		auto declName = Declaration->getDeclName();

		if (!declName.isIdentifier() && declName.getCXXOverloadedOperator() == OO_None)
		{
			log("Invalid declName");
			return false;
		}

		auto declNameStr = declName.getAsString();
		if (declNameStr.empty())
		{
			log("Empty declName");
			return false;
		}

		if (!((lexContext->isNamespace() || lexContext->isTranslationUnit()) && (context->isNamespace() || context->isTranslationUnit())))
		{
			log("Invalid context");
			return false;
		}

		if ((!context->isNamespace() && !context->isTranslationUnit()))
		{
			log("Invalid context");
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
			log("Invalid file");
			return false;
		}
		auto filePath = std::filesystem::path{std::string{file->getName()}}.lexically_normal();
		if (!filePathToIncludeNameMap.contains(filePath))
		{
			log("File path is not one of the expected ones");
			return false;
		}

		auto namespaceName = getNamespaceName(Declaration);

		{
			if (!allowReservedNames)
			{
				std::vector<NamespaceInfo> namespaceInfo = getNamespaceAncestryInfo(context);
				if (!namespaceInfo.empty() && !isUnreservedName(namespaceInfo.back().name, true))
				{
					log("Invalid namespace name");
					return false;
				}
				for (auto const& ns : namespaceInfo | std::views::reverse | std::views::drop(1))
				{
					if (!isUnreservedName(ns.name, false))
					{
						log("Reserved namespace name");
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
				log("Namespace not in whitelist");
				return false;
			}

			// If the blacklist is not empty, and the namespace is in the blacklist, this is not valid
			if (std::find_if(configuration.NamespaceBlacklist.begin(), configuration.NamespaceBlacklist.end(), namespace_matches) != configuration.NamespaceBlacklist.end())
			{
				log("Namespace in blacklist");
				return false;
			}
		}

		if (!allowReservedNames && !isUnreservedName(declNameStr, context->isTranslationUnit()))
		{
			log("Reserved name");
			return false;
		}

		log("Valid declaration");

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

		auto lexContext = Declaration->getLexicalDeclContext();
		auto context = Declaration->getDeclContext();
		if (context->isExternCContext())
		{
			context = context->getParent();
		}

		// std::string declName = Declaration->getDeclName().getAsString();

		globalNamespace.ensureNamespace(getNamespaceAncestryInfo(context)).addUsingDeclToNamespace(declName);
		return true;
	}
};
} // namespace gencppm
