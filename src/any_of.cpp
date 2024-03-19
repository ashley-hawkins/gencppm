export module gencppm:any_of;

import std;

import LLVM.Support;

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
