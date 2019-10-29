#pragma once

#if defined(__has_include) && __has_include(<version>)
#	include <version>
#endif

#if __has_cpp_attribute(nodiscard)
#	ifdef __clang__
		// NOLINTNEXTLINE
#		define COW_NODISCARD __attribute__((warn_unused_result))
#	else
#		define COW_NODISCARD [[nodiscard]]
#	endif
#else
#	define COW_NODISCARD
#endif

#if (defined(__cpp_lib_optional) && __cpp_lib_optional >= 201606) || __cplusplus >= 201703L
#	define COW_CPP_LIB_OPTIONAL
#endif
