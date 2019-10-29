#pragma once
#include "compile_features.h"
#include <utility>

namespace cow {
namespace detail {
namespace compatibility {

#ifdef COW_CPP_LIB_OPTIONAL
using std::in_place_t; // NOLINT(misc-unused-using-decls)
using std::in_place; // NOLINT(misc-unused-using-decls)
#else
struct in_place_t {};
constexpr in_place_t in_place;
#endif

} // namespace compatibility
} // namespace detail
} // namespace cow
