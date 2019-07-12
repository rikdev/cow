#pragma once

#if __has_cpp_attribute(nodiscard)
#	if __clang__
		// NOLINTNEXTLINE
#		define COW_NODISCARD __attribute__((warn_unused_result))
#	else
#		define COW_NODISCARD [[nodiscard]]
#	endif
#else
#	define COW_NODISCARD
#endif
