#pragma once
#include <utility>

namespace cow {
namespace detail {
namespace compatibility {

#if __cpp_lib_optional
using std::in_place_t;
using std::in_place;
#else
struct in_place_t {};
constexpr in_place_t in_place;
#endif

} // namespace compatibility
} // namespace detail
} // namespace cow
