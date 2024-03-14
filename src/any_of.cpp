module;
#include <type_traits>
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
} // namespace gencppm
