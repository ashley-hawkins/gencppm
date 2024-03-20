/*
 * SPDX-FileCopyrightText: © 2024 Ashley Hawkins <awhawkins@proton.me>
 * SPDX-FileContributor: Ashley Hawkins <awhawkins@proton.me>
 *
 * SPDX-License-Identifier: AGPL-3.0-only
 */
module;
#include "includefirst.hpp"

#include <type_traits>
#include <utility>

#include <llvm/Support/Casting.h>
export module gencppm:any_of;

export namespace gencppm
{
template <typename T, typename... Ts>
struct is_any_of : std::disjunction<std::is_same<T, Ts>...>
{
};

template <typename... Ts>
inline constexpr bool is_any_of_v = is_any_of<Ts...>::value;

template <typename... Ts>
concept any_of = is_any_of_v<Ts...>;

template <typename... Types>
bool isany(auto&& Declaration)
{
	return (llvm::isa<Types>(std::forward<decltype(Declaration)>(Declaration)) || ...);
}
} // namespace gencppm
