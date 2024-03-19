/*
 * SPDX-FileCopyrightText: © 2024 Ashley Hawkins <awhawkins@proton.me>
 * SPDX-FileContributor: Ashley Hawkins <awhawkins@proton.me>
 *
 * SPDX-License-Identifier: AGPL-3.0-only
 */

export module gencppm:namespaces;

import std;

export namespace gencppm
{
using FilePathToIncludeNameMap = std::unordered_map<std::filesystem::path, std::string>;
struct NamespaceAlias
{
	std::string name;
	std::string aliasedName;
	bool operator==(NamespaceAlias const& other) const
	{
		return name == other.name && aliasedName == other.aliasedName;
	}
};

struct NamespaceInfo
{
	std::string name;
	bool isInline;
};

struct Namespace
{
	using Child = std::variant<Namespace, NamespaceAlias, std::string>;
	std::string name;
	bool isInline;
	std::vector<Child> children;

	bool operator==(Namespace const& other) const
	{
		return name == other.name && children == other.children;
	}

	Namespace& ensureNamespace(std::ranges::range auto&& namespaceAncestryInfo)
	{
		return ensureNamespaceIterative(namespaceAncestryInfo);
	}

	void addUsingDeclToNamespace(std::string_view name)
	{
		if (std::ranges::contains(children, Namespace::Child(std::string(name))))
		{
			return;
		}
		children.push_back(std::string(name));
	}

	void addNamespaceAliasToNamespace(NamespaceAlias decl)
	{
		if (std::ranges::contains(children, Namespace::Child(decl)))
		{
			return;
		}
		children.push_back(decl);
	}

private:
	Namespace& ensureNamespaceIterative(std::ranges::range auto&& namespaceAncestryInfo)
	{
		Namespace* currentNamespace = this;
		for (NamespaceInfo const& namespaceInfo : namespaceAncestryInfo | std::views::reverse)
		{
			Namespace* nextNamespace = nullptr;

			// Check if children contains a namespace with the same name
			auto it = std::find_if(currentNamespace->children.begin(), currentNamespace->children.end(), [&](auto&& child) {
				if (Namespace* ns = std::get_if<Namespace>(&child))
				{
					return std::string_view{ns->name} == std::string_view{namespaceInfo.name} && ns->isInline == namespaceInfo.isInline;
				}
				return false;
			});

			if (it != currentNamespace->children.end())
			{
				// If it does, add the next component to that namespace
				nextNamespace = &std::get<Namespace>(*it);
			}
			else
			{
				// If it doesn't, add a new namespace with the next component
				auto& newNamespace = currentNamespace->children.emplace_back(Namespace{namespaceInfo.name, namespaceInfo.isInline, {}});
				nextNamespace = &std::get<Namespace>(newNamespace);
				// std::println("Created namespace: {}", nextNamespace->name);
			}

			currentNamespace = nextNamespace;
		}
		return *currentNamespace;
	}
};
}; // namespace gencppm
