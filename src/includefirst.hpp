// Include these first to work around clang bug with false positive ODR violations
#include <cstddef>
#include <cstdint>
#if __has_include(<compare>)
#include <compare>
#endif
