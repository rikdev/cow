#pragma once
#include "detail/compatibility/compile_features.h"
#include "detail/compatibility/utility.h"
#include <array>
#include <cstddef>
#include <exception>
#include <functional>
#include <initializer_list>
#include <memory>
#include <tuple>
#include <type_traits>
#include <utility>

#if __cpp_lib_optional
#include <optional>
#endif

/*
synopsis

namespace cow {

#if __cpp_lib_optional
/// If an object of type T Is more efficient to copy than `std::shared_ptr`,
/// then this template allows not to use copy-on-write optimization for this type
template<typename T>
struct allow_inplace_placement;
#endif

/// The struct `nullopt_t` is an empty structure type used to indicate `optional` type with uninitialized state.
struct nullopt_t;
/// It is a constant of type `nullopt_t` that is used to indicate `optional` type with uninitialized state.
constexpr nullopt_t nullopt;

/// The class `bad_optional_access` defines the type of objects thrown as exceptions to report the situation where an
/// attempt is made to access the value of an `optional` object that does not contain a value.
class bad_optional_access;

// relational operations

template<typename T, bool UseInlineStorage1, typename U, bool UseInlineStorage2>
constexpr bool operator==(const optional<T, UseInlineStorage1>& lhs, const optional<U, UseInlineStorage2>& rhs);

template<typename T, bool UseInlineStorage1, typename U, bool UseInlineStorage2>
constexpr bool operator!=(const optional<T, UseInlineStorage1>& lhs, const optional<U, UseInlineStorage2>& rhs);

template<typename T, bool UseInlineStorage1, typename U, bool UseInlineStorage2>
constexpr bool operator<(const optional<T, UseInlineStorage1>& lhs, const optional<U, UseInlineStorage2>& rhs);

template<typename T, bool UseInlineStorage1, typename U, bool UseInlineStorage2>
constexpr bool operator>(const optional<T, UseInlineStorage1>& lhs, const optional<U, UseInlineStorage2>& rhs);

template<typename T, bool UseInlineStorage1, typename U, bool UseInlineStorage2>
constexpr bool operator<=(const optional<T, UseInlineStorage1>& lhs, const optional<U, UseInlineStorage2>& rhs);

template<typename T, bool UseInlineStorage1, typename U, bool UseInlineStorage2>
constexpr bool operator>=(const optional<T, UseInlineStorage1>& lhs, const optional<U, UseInlineStorage2>& rhs);

// comparison with nullopt

template<typename T, bool UseInlineStorage>
constexpr bool operator==(const optional<T, UseInlineStorage>& lhs, nullopt_t) noexcept;

template<typename T, bool UseInlineStorage>
constexpr bool operator==(nullopt_t, const optional<T, UseInlineStorage>& rhs) noexcept;

template<typename T, bool UseInlineStorage>
constexpr bool operator!=(const optional<T, UseInlineStorage>& lhs, nullopt_t) noexcept;

template<typename T, bool UseInlineStorage>
constexpr bool operator!=(nullopt_t, const optional<T, UseInlineStorage>& rhs) noexcept;

template<typename T, bool UseInlineStorage>
constexpr bool operator<(const optional<T, UseInlineStorage>&, nullopt_t) noexcept;

template<typename T, bool UseInlineStorage>
constexpr bool operator<(nullopt_t, const optional<T, UseInlineStorage>& rhs) noexcept;

template<typename T, bool UseInlineStorage>
constexpr bool operator<=(const optional<T, UseInlineStorage>& lhs, nullopt_t) noexcept;

template<typename T, bool UseInlineStorage>
constexpr bool operator<=(nullopt_t, const optional<T, UseInlineStorage>&) noexcept;

template<typename T, bool UseInlineStorage>
constexpr bool operator>(const optional<T, UseInlineStorage>& lhs, nullopt_t) noexcept;

template<typename T, bool UseInlineStorage>
constexpr bool operator>(nullopt_t, const optional<T, UseInlineStorage>&) noexcept;

template<typename T, bool UseInlineStorage>
constexpr bool operator>=(const optional<T, UseInlineStorage>&, nullopt_t) noexcept;

template<typename T, bool UseInlineStorage>
constexpr bool operator>=(nullopt_t, const optional<T, UseInlineStorage>& rhs) noexcept;

// comparison with T

template<typename T, bool UseInlineStorage, typename U>
constexpr bool operator==(const optional<T, UseInlineStorage>& lhs, const U& rhs);

template<typename T, bool UseInlineStorage, typename U>
constexpr bool operator==(const U& lhs, const optional<T, UseInlineStorage>& rhs);

template<typename T, bool UseInlineStorage, typename U>
constexpr bool operator!=(const optional<T, UseInlineStorage>& lhs, const U& rhs);

template<typename T, bool UseInlineStorage, typename U>
constexpr bool operator!=(const U& lhs, const optional<T, UseInlineStorage>& rhs);

template<typename T, bool UseInlineStorage, typename U>
constexpr bool operator<(const optional<T, UseInlineStorage>& lhs, const U& rhs);

template<typename T, bool UseInlineStorage, typename U>
constexpr bool operator<(const U& lhs, const optional<T, UseInlineStorage>& rhs);

template<typename T, bool UseInlineStorage, typename U>
constexpr bool operator<=(const optional<T, UseInlineStorage>& lhs, const U& rhs);

template<typename T, bool UseInlineStorage, typename U>
constexpr bool operator<=(const U& lhs, const optional<T, UseInlineStorage>& rhs);

template<typename T, bool UseInlineStorage, typename U>
constexpr bool operator>(const optional<T, UseInlineStorage>& lhs, const U& rhs);

template<typename T, bool UseInlineStorage, typename U>
constexpr bool operator>(const U& lhs, const optional<T, UseInlineStorage>& rhs);

template<typename T, bool UseInlineStorage, typename U>
constexpr bool operator>=(const optional<T, UseInlineStorage>& lhs, const U& rhs);

template<typename T, bool UseInlineStorage, typename U>
constexpr bool operator>=(const U& lhs, const optional<T, UseInlineStorage>& rhs);

// specialized algorithms

template<typename T>
void swap(optional<T>& lhs, optional<T>& rhs)
	noexcept(std::is_nothrow_move_constructible<T>::value && std::is_nothrow_swappable<T>::value);

template<typename T, bool UseInlineStorage = use_inline_storage_v<T>>
constexpr optional<std::decay_t<T>, UseInlineStorage> make_optional(T&& v);

template<typename T, bool UseInlineStorage = use_inline_storage_v<T>, typename...Args>
constexpr optional<T, UseInlineStorage> make_optional(Args&&... args);

template<typename T, bool UseInlineStorage = use_inline_storage_v<T>, typename U, typename... Args>
constexpr optional<T, UseInlineStorage> make_optional(std::initializer_list<U> ilist, Args&&... args);

/// The class `optional` implements copy-on-write storage and provides `std::optional` like interface.
/// \tparam T Value type.
/// \tparam UseInlineStorage If false one value of T shared between all copies of the `optional` object.
///                          If true each copy of the `optional` object keep own copy of value object (small
///                          buffer optimization).
template<typename T, bool UseInlineStorage = use_inline_storage_v<T>>
class optional
{
	using value_type = T;

	// constructors

	constexpr optional() noexcept;
	constexpr optional(nullopt_t) noexcept;
	constexpr optional(const optional&);
	constexpr optional(optional&&) noexcept(std::is_nothrow_move_constructible_v<T>);

	template<typename... Args>
	constexpr explicit optional(in_place_t, Args&&... args);

	template<typename U, typename... Args>
	constexpr explicit optional(in_place_t, std::initializer_list<U> ilist, Args&&... args);

	template<typename U = T>
	constexpr EXPLICIT optional(U&& value);

	template<typename U>
	EXPLICIT optional(const optional<U>& other);

	template<typename U>
	EXPLICIT optional(optional<U>&& other);

	// destructor

	~optional();

	// assignments

	optional& operator=(nullopt_t) noexcept;
	optional& operator=(const optional&);
	optional& operator=(optional&&) noexcept(std::is_nothrow_move_constructible_v<T>);

	template<typename U = T>
	optional& operator=(U&& value);

	template<typename U = T>
	optional& operator=(const optional<U>& other);

	template<typename U = T>
	optional& operator=(optional<U, true>&& other);

	// swap

	void swap(optional& other)
		noexcept(std::is_nothrow_move_constructible<T>::value && std::is_nothrow_swappable<T>::value);

	// observers

	constexpr const T* operator->() const;
	constexpr const T& operator*() const&;
	constexpr T&& operator*() &&;
	constexpr const T&& operator*() const&&;

	explicit operator bool() const noexcept;
	constexpr bool has_value() const noexcept;

	/// \throw bad_optional_access if `has_value() == false`.
	constexpr const T& value() const&;
	/// \throw bad_optional_access if `has_value() == false`.
	constexpr const T&& value() const&&;

	template<typename U>
	constexpr T value_or(U&& default_value) const&;

	template<typename U>
	constexpr T value_or(U&& default_value) &&;

	// modifiers

	void reset() noexcept;
};

#if __cpp_deduction_guides
template<typename T>
optional(T) -> optional<T>;
#endif

} // namespace cow

namespace std {

template<typename T, bool UseInlineStorage>
struct hash<cow::optional<T, UseInlineStorage>>;

} // namespace std
*/

namespace cow {

#if __cpp_lib_optional
// allow_inplace_placement
template<typename T>
struct allow_inplace_placement
	: std::conjunction<std::is_trivially_copy_constructible<T>, std::is_trivially_copy_assignable<T>> {};

template<typename T>
struct allow_inplace_placement<std::shared_ptr<T>> : std::true_type {};

template<typename T>
struct allow_inplace_placement<std::weak_ptr<T>> : std::true_type {};

template<>
struct allow_inplace_placement<std::exception_ptr> : std::true_type {};

template<typename... Ts>
struct allow_inplace_placement<std::tuple<Ts...>> : std::conjunction<allow_inplace_placement<Ts>...> {};

template<typename... Ts>
struct allow_inplace_placement<std::pair<Ts...>> : std::conjunction<allow_inplace_placement<Ts>...> {};

template<typename T, std::size_t N>
struct allow_inplace_placement<std::array<T, N>> : allow_inplace_placement<T> {};

// use_inline_storage
template<typename T, std::size_t MaxInlineStorageSize>
struct use_inline_storage :
	std::bool_constant<allow_inplace_placement<T>::value && sizeof(T) <= MaxInlineStorageSize> {};

using std::nullopt_t;
using std::nullopt;
using std::bad_optional_access;
#else
template<typename T, std::size_t MaxInlineStorageSize>
struct use_inline_storage : std::false_type {};

struct nullopt_t {};
constexpr nullopt_t nullopt;

struct bad_optional_access : std::exception {
	COW_NODISCARD const char* what() const noexcept override {
		return "Bad optional access";
	}
};
#endif

using detail::compatibility::in_place_t;
using detail::compatibility::in_place;

template<typename T, std::size_t MaxInlineStorageSize = sizeof(std::shared_ptr<T>)>
constexpr bool use_inline_storage_v = use_inline_storage<T, MaxInlineStorageSize>::value;

/// The class `optional` implements copy-on-write storage and provides `std::optional` like interface.
/// \tparam T Value type.
/// \tparam UseInlineStorage If false one value of T shared between all copies of the `optional` object.
///                          If true each copy of the `optional` object keep own copy of value object (small
///                          buffer optimization).
template<typename T, bool UseInlineStorage = use_inline_storage_v<T>>
class optional;

namespace optional_detail {

template<typename ToOptional, typename U>
struct direct_conversation {
	using to_value_type = typename ToOptional::value_type;

	static constexpr bool allow =
		std::is_constructible<to_value_type, U&&>::value
		&& !std::is_same<std::decay_t<U>, in_place_t>::value
		&& !std::is_same<std::decay_t<U>, ToOptional>::value;

	static constexpr bool allow_implicit = std::is_convertible<U&&, to_value_type>::value && allow;
	static constexpr bool allow_explicit = !std::is_convertible<U&&, to_value_type>::value && allow;
};

template<typename T, typename FromOptional>
struct unwrapping {
	using from_value_type = typename FromOptional::value_type;

	static constexpr bool allow =
		!std::is_constructible<T, FromOptional&>::value
		&& !std::is_constructible<T, FromOptional&&>::value
		&& !std::is_constructible<T, const FromOptional&>::value
		&& !std::is_constructible<T, const FromOptional&&>::value
		&& !std::is_convertible<FromOptional&, T>::value
		&& !std::is_convertible<FromOptional&&, T>::value
		&& !std::is_convertible<const FromOptional&, T>::value
		&& !std::is_convertible<const FromOptional&&, T>::value;

	static constexpr bool allow_copy =
		std::is_constructible<T, const from_value_type&>::value
		&& allow;

	static constexpr bool allow_copy_implicit =
		std::is_convertible<const from_value_type&, T>::value
		&& allow_copy;

	static constexpr bool allow_copy_explicit =
		!std::is_convertible<const from_value_type&, T>::value
		&& allow_copy;

	static constexpr bool allow_move =
		std::is_constructible<T, from_value_type&&>::value
		&& allow;

	static constexpr bool allow_move_implicit =
		std::is_convertible<from_value_type&&, T>::value
		&& allow_move;

	static constexpr bool allow_move_explicit =
		!std::is_convertible<from_value_type&&, T>::value
		&& allow_move;
};

template<typename ToOptional, typename U>
struct assign_direct_conversation {
	using to_value_type = typename ToOptional::value_type;

	static constexpr bool allow =
		!std::is_same<std::decay_t<U>, ToOptional>::value
		&& !(std::is_scalar<to_value_type>::value && std::is_same<to_value_type, std::decay_t<U>>::value)
		&& std::is_constructible<to_value_type, U>::value
		&& std::is_assignable<to_value_type&, U>::value;
};

template<typename T, typename FromOptional>
struct assing_unwrapping {
	using from_value_type = typename FromOptional::value_type;

	static constexpr bool allow =
		unwrapping<T, FromOptional>::allow
		&& !std::is_assignable<T&, FromOptional&>::value
		&& !std::is_assignable<T&, FromOptional&&>::value
		&& !std::is_assignable<T&, const FromOptional&>::value
		&& !std::is_assignable<T&, const FromOptional&&>::value;

	static constexpr bool allow_copy =
		std::is_constructible<T, const from_value_type&>::value
		&& std::is_assignable<T&, const from_value_type&>::value
		&& allow;

	static constexpr bool allow_move =
		std::is_constructible<T, from_value_type>::value
		&& std::is_assignable<T&, from_value_type>::value
		&& allow;
};

} // namespace optional_detail

template<typename T>
class optional<T, false> {
	static_assert(
		!std::is_reference<T>::value, "Instantiation of optional with a reference type is ill-formed");
	static_assert(
		!std::is_same<std::decay_t<T>, in_place_t>::value, "Instantiation of optional with in_place_t is ill-formed");
	static_assert(
		!std::is_same<std::decay_t<T>, nullopt_t>::value, "Instantiation of optional with nullopt_t is ill-formed");
	static_assert(
		std::is_destructible<T>::value, "Instantiation of optional with a non-destructible type is ill-formed");

	template<typename, bool>
	friend class optional;

public:
	using value_type = T;

	// constructors

	optional() = default;

	constexpr optional(nullopt_t) noexcept // NOLINT: Allow implicit conversion
		: optional{}
	{}

	optional(const optional&) = default;
	optional(optional&&) = default;

	template<typename... Args, typename = std::enable_if_t<std::is_constructible<T, Args...>::value>>
	constexpr explicit optional(in_place_t, Args&&... args)
		: data_{std::make_shared<value_type>(std::forward<Args>(args)...)}
	{}

	template<
		typename U,
		typename... Args,
		typename = std::enable_if_t<std::is_constructible<T, std::initializer_list<U>&, Args&&...>::value>>
	constexpr explicit optional(in_place_t, std::initializer_list<U> ilist, Args&&... args)
		: data_{std::make_shared<value_type>(ilist, std::forward<Args>(args)...)}
	{}

	template<
		typename U = T, std::enable_if_t<optional_detail::direct_conversation<optional, U>::allow_implicit, int> = 0>
	constexpr optional(U&& value) // NOLINT: Allow implicit conversion
		: optional{in_place, std::forward<U>(value)}
	{}

	template<
		typename U = T, std::enable_if_t<optional_detail::direct_conversation<optional, U>::allow_explicit, int> = 0>
	constexpr explicit optional(U&& value)
		: optional{in_place, std::forward<U>(value)}
	{}

	template<
		typename U,
		std::enable_if_t<
			std::is_convertible<U*, T*>::value && optional_detail::unwrapping<T, optional<U, false>>::allow_copy,
			int> = 0>
	optional(const optional<U, false>& other) noexcept // NOLINT: Allow implicit conversion
		: data_{other.data_}
	{}

	// non-cow constructor
	template<
		typename U,
		std::enable_if_t<
			!std::is_convertible<U*, T*>::value && optional_detail::unwrapping<T, optional<U, false>>::allow_copy,
			int> = 0>
	explicit optional(const optional<U, false>& other)
		: data_{other ? std::make_shared<value_type>(*other) : nullptr}
	{}


#if __cpp_lib_optional
	// non-cow constructor
	template<typename U, std::enable_if_t<optional_detail::unwrapping<T, optional<U, true>>::allow_copy, int> = 0>
	explicit optional(const optional<U, true>& other)
		: data_{other ? std::make_shared<value_type>(*other) : nullptr}
	{}
#endif

	template<typename U, std::enable_if_t<std::is_convertible<U*, T*>::value, int> = 0>
	optional(optional<U, false>&& other) noexcept // NOLINT: Allow implicit conversion
		: data_{std::move(other.data_)}
	{}

	// non-cow constructor
	template<
		typename U,
		std::enable_if_t<
			!std::is_convertible<U*, T*>::value && optional_detail::unwrapping<T, optional<U, false>>::allow_move,
			int> = 0>
	explicit optional(optional<U, false>&& other)
		: data_{other ? std::make_shared<value_type>(*std::move(other)) : nullptr}
	{}

#if __cpp_lib_optional
	// non-cow constructor
	template<typename U, std::enable_if_t<optional_detail::unwrapping<T, optional<U, true>>::allow_move, int> = 0>
	explicit optional(optional<U, true>&& other)
		: data_{other ? std::make_shared<value_type>(*std::move(other)) : nullptr}
	{}
#endif

	// destructor
	~optional() = default;

	// assignments

	optional& operator=(nullopt_t) noexcept
	{
		reset();
		return *this;
	}

	optional& operator=(const optional&) = default;
	optional& operator=(optional&&) = default;

	template<
		typename U = T, typename = std::enable_if_t<optional_detail::assign_direct_conversation<optional, U>::allow>>
	optional& operator=(U&& value)
	{
		set_value(std::forward<U>(value));
		return *this;
	}

	template<
		typename U = T,
		std::enable_if_t<
			std::is_convertible<U*, T*>::value && optional_detail::assing_unwrapping<T, optional<U, false>>::allow_copy,
			int> = 0>
	optional& operator=(const optional<U, false>& other) noexcept
	{
		data_ = other.data_;
		return *this;
	}

	// non-cow assignment
	template<
		typename U = T,
		std::enable_if_t<
			!std::is_convertible<U*, T*>::value && optional_detail::assing_unwrapping<T, optional<U, false>>::allow_copy,
			int> = 0>
	optional& operator=(const optional<U, false>& other)
	{
		if (other)
			set_value(*other);
		else
			reset();

		return *this;
	}

#if __cpp_lib_optional
	// non-cow assignment
	template<
		typename U = T, std::enable_if_t<optional_detail::assing_unwrapping<T, optional<U, true>>::allow_copy, int> = 0>
	optional& operator=(const optional<U, true>& other)
	{
		if (other)
			set_value(*other);
		else
			reset();

		return *this;
	}
#endif

	template<
		typename U = T,
		std::enable_if_t<
			std::is_convertible<U*, T*>::value && optional_detail::assing_unwrapping<T, optional<U, false>>::allow_move,
			int> = 0>
	optional& operator=(optional<U, false>&& other) noexcept
	{
		data_ = std::move(other.data_);
		return *this;
	}

	// non-cow assignment
	template<
		typename U = T,
		std::enable_if_t<
			!std::is_convertible<U*, T*>::value
			&& optional_detail::assing_unwrapping<T, optional<U, false>>::allow_move,
			int> = 0>
	optional& operator=(optional<U, false>&& other)
	{
		if (other)
			set_value(*std::move(other));
		else
			reset();

		return *this;
	}

#if __cpp_lib_optional
	// non-cow assignment
	template<
		typename U = T, std::enable_if_t<optional_detail::assing_unwrapping<T, optional<U, true>>::allow_move, int> = 0>
	optional& operator=(optional<U, true>&& other)
	{
		if (other)
			set_value(*std::move(other));
		else
			reset();

		return *this;
	}
#endif

	// swap

	void swap(optional& other) noexcept
	{
		data_.swap(other.data_);
	}

	// observers

	COW_NODISCARD constexpr const T* operator->() const noexcept
	{
		return data_.get();
	}

	COW_NODISCARD constexpr const T& operator*() const& noexcept
	{
		return *data_;
	}

	COW_NODISCARD constexpr const T&& operator*() const&& noexcept
	{
		return std::move(*data_);
	}

	constexpr explicit operator bool() const noexcept
	{
		return has_value();
	}

	COW_NODISCARD constexpr bool has_value() const noexcept
	{
		return static_cast<bool>(data_);
	}

	COW_NODISCARD constexpr const T& value() const&
	{
		if (!data_)
			throw bad_optional_access{};

		return *data_;
	}

	COW_NODISCARD constexpr const T&& value() const&&
	{
		if (!data_)
			throw bad_optional_access{};

		return std::move(*data_);
	}

	template<typename U>
	COW_NODISCARD constexpr T value_or(U&& default_value) const&
	{
		if (!data_)
			return static_cast<value_type>(std::forward<U>(default_value));

		return *data_;
	}

	template<typename U>
	COW_NODISCARD constexpr T value_or(U&& default_value) &&
	{
		if (!data_)
			return static_cast<value_type>(std::forward<U>(default_value));

		if (data_.use_count() == 1)
			return std::move(*data_);

		return *data_;
	}

	// modifiers

	void reset() noexcept
	{
		data_.reset();
	}

private:
	template<typename U>
	void set_value(U&& value)
	{
		if (data_.use_count() == 1)
			*data_ = std::forward<U>(value);
		else
			data_ = std::make_shared<value_type>(std::forward<U>(value));
	}

	std::shared_ptr<value_type> data_;
};


// specialized algorithms

template<typename T>
void swap(optional<T, false>& lhs, optional<T, false>& rhs) noexcept
{
	lhs.swap(rhs);
}

#if __cpp_lib_optional
template<typename T>
class optional<T, true> {
	template<typename, bool>
	friend class optional;

public:
	using value_type = T;

	// constructors

	optional() = default;

	constexpr optional(nullopt_t) noexcept // NOLINT: Allow implicit conversion
		: data_{std::nullopt}
	{}

	optional(const optional&) = default;
	optional(optional&&) = default;

	template<typename... Args, typename = std::enable_if_t<std::is_constructible<T, Args...>::value>>
	constexpr explicit optional(in_place_t, Args&&... args)
		: data_{std::in_place, std::forward<Args>(args)...}
	{}

	template<
		typename U,
		typename... Args,
		typename = std::enable_if_t<std::is_constructible<T, std::initializer_list<U>&, Args&&...>::value>>
	constexpr explicit optional(in_place_t, std::initializer_list<U> ilist, Args&&... args)
		: data_{std::in_place, ilist, std::forward<Args>(args)...}
	{}

	template<
		typename U = T, std::enable_if_t<optional_detail::direct_conversation<optional, U>::allow_implicit, int> = 0>
	constexpr optional(U&& value) // NOLINT: Allow implicit conversion
		: data_{std::forward<U>(value)}
	{}

	template<
		typename U = T, std::enable_if_t<optional_detail::direct_conversation<optional, U>::allow_explicit, int> = 0>
	constexpr explicit optional(U&& value)
		: data_{std::forward<U>(value)}
	{}

	template<
		typename U, std::enable_if_t<optional_detail::unwrapping<T, optional<U, true>>::allow_copy_implicit, int> = 0>
	optional(const optional<U, true>& other) // NOLINT: Allow implicit conversion
		: data_{other.data_}
	{}

	template<
		typename U, std::enable_if_t<optional_detail::unwrapping<T, optional<U, false>>::allow_copy_implicit, int> = 0>
	optional(const optional<U, false>& other) // NOLINT: Allow implicit conversion
		: data_{other ? decltype(data_)(*other) : nullopt}
	{}

	template<
		typename U, std::enable_if_t<optional_detail::unwrapping<T, optional<U, true>>::allow_copy_explicit, int> = 0>
	explicit optional(const optional<U, true>& other)
		: data_{other.data_}
	{}

	template<
		typename U, std::enable_if_t<optional_detail::unwrapping<T, optional<U, false>>::allow_copy_explicit, int> = 0>
	explicit optional(const optional<U, false>& other)
		: data_{other ? decltype(data_)(*other) : nullopt}
	{}

	template<
		typename U, std::enable_if_t<optional_detail::unwrapping<T, optional<U, true>>::allow_move_implicit, int> = 0>
	optional(optional<U, true>&& other) // NOLINT: Allow implicit conversion
		: data_{std::move(other.data_)}
	{}

	template<
		typename U, std::enable_if_t<optional_detail::unwrapping<T, optional<U, false>>::allow_move_implicit, int> = 0>
	optional(optional<U, false>&& other) // NOLINT: Allow implicit conversion
		: data_{other ? decltype(data_)(*std::move(other)) : nullopt}
	{}

	template<
		typename U, std::enable_if_t<optional_detail::unwrapping<T, optional<U, true>>::allow_move_explicit, int> = 0>
	explicit optional(optional<U, true>&& other)
		: data_{std::move(other.data_)}
	{}

	template<
		typename U, std::enable_if_t<optional_detail::unwrapping<T, optional<U, false>>::allow_move_explicit, int> = 0>
	explicit optional(optional<U, false>&& other)
		: data_{other ? decltype(data_)(*std::move(other)) : nullopt}
	{}

	// destructor

	~optional() = default;

	// assignments

	optional& operator=(nullopt_t) noexcept
	{
		data_ = std::nullopt;
		return *this;
	}

	optional& operator=(const optional&) = default;
	optional& operator=(optional&&) = default;

	template<
		typename U = T, typename = std::enable_if_t<optional_detail::assign_direct_conversation<optional, U>::allow>>
	optional& operator=(U&& value)
	{
		data_ = std::forward<U>(value);
		return *this;
	}

	template<
		typename U = T,
		typename = std::enable_if_t<optional_detail::assing_unwrapping<T, optional<U, true>>::allow_copy>>
	optional& operator=(const optional<U, true>& other)
	{
		data_ = other.data_;
		return *this;
	}

	template<
		typename U = T,
		typename = std::enable_if_t<optional_detail::assing_unwrapping<T, optional<U, false>>::allow_copy>>
	optional& operator=(const optional<U, false>& other)
	{
		if (other)
			data_ = *other;
		else
			reset();

		return *this;
	}

	template<
		typename U = T,
		typename = std::enable_if_t<optional_detail::assing_unwrapping<T, optional<U, true>>::allow_move>>
	optional& operator=(optional<U, true>&& other)
	{
		data_ = std::move(other.data_);
		return *this;
	}

	template<
		typename U = T,
		typename = std::enable_if_t<optional_detail::assing_unwrapping<T, optional<U, false>>::allow_move>>
	optional& operator=(optional<U, false>&& other)
	{
		if (other)
			data_ = *std::move(other);
		else
			reset();

		return *this;
	}

	// swap

	void swap(optional& other)
		noexcept(std::is_nothrow_move_constructible<T>::value && std::is_nothrow_swappable<T>::value)
	{
		data_.swap(other.data_);
	}

	// observers

	COW_NODISCARD constexpr const T* operator->() const
	{
		return data_.operator->();
	}

	COW_NODISCARD constexpr const T& operator*() const&
	{
		return data_.operator*();
	}

	COW_NODISCARD constexpr T&& operator*() &&
	{
		return std::move(data_).operator*();
	}

	COW_NODISCARD constexpr const T&& operator*() const&&
	{
		return std::move(data_).operator*();
	}

	constexpr explicit operator bool() const noexcept
	{
		return static_cast<bool>(data_);
	}

	COW_NODISCARD constexpr bool has_value() const noexcept
	{
		return data_.has_value();
	}

	COW_NODISCARD constexpr const T& value() const&
	{
		return data_.value();
	}

	COW_NODISCARD constexpr T&& value() &&
	{
		return std::move(data_).value();
	}

	COW_NODISCARD constexpr const T&& value() const&&
	{
		return std::move(data_).value();
	}

	template<typename U>
	COW_NODISCARD constexpr T value_or(U&& default_value) const&
	{
		return data_.value_or(std::forward<U>(default_value));
	}

	template<typename U>
	COW_NODISCARD constexpr T value_or(U&& default_value) &&
	{
		return std::move(data_).value_or(std::forward<U>(default_value));
	}

	// modifiers

	void reset() noexcept
	{
		data_.reset();
	}

private:
	std::optional<value_type> data_;
};

// specialized algorithms

template<typename T>
std::enable_if_t<std::is_move_constructible<T>::value&& std::is_swappable<T>::value>
swap(optional<T, true>& lhs, optional<T, true>& rhs) noexcept(noexcept(lhs.swap(rhs)))
{
	lhs.swap(rhs);
}
#endif

#if __cpp_deduction_guides
template<typename T>
optional(T) -> optional<T>;
#endif

// # non-member functions

// ## relational operations

template<typename T, bool UseInlineStorage1, typename U, bool UseInlineStorage2>
COW_NODISCARD constexpr bool operator==(
	const optional<T, UseInlineStorage1>& lhs, const optional<U, UseInlineStorage2>& rhs)
{
	if (static_cast<bool>(lhs) != static_cast<bool>(rhs))
		return false;

	if (!lhs)
		return true;

	return *lhs == *rhs;
}

template<typename T, bool UseInlineStorage1, typename U, bool UseInlineStorage2>
COW_NODISCARD constexpr bool operator!=(
	const optional<T, UseInlineStorage1>& lhs, const optional<U, UseInlineStorage2>& rhs)
{
	if (static_cast<bool>(lhs) != static_cast<bool>(rhs))
		return true;

	if (!lhs)
		return false;

	return *lhs != *rhs;
}

template<typename T, bool UseInlineStorage1, typename U, bool UseInlineStorage2>
COW_NODISCARD constexpr bool operator<(
	const optional<T, UseInlineStorage1>& lhs, const optional<U, UseInlineStorage2>& rhs)
{
	if (!rhs)
		return false;

	if (!lhs)
		return true;

	return *lhs < *rhs;
}

template<typename T, bool UseInlineStorage1, typename U, bool UseInlineStorage2>
COW_NODISCARD constexpr bool operator>(
	const optional<T, UseInlineStorage1>& lhs, const optional<U, UseInlineStorage2>& rhs)
{
	if (!lhs)
		return false;

	if (!rhs)
		return true;

	return *lhs > *rhs;
}

template<typename T, bool UseInlineStorage1, typename U, bool UseInlineStorage2>
COW_NODISCARD constexpr bool operator<=(
	const optional<T, UseInlineStorage1>& lhs, const optional<U, UseInlineStorage2>& rhs)
{
	if (!lhs)
		return true;

	if (!rhs)
		return false;

	return *lhs <= *rhs;
}

template<typename T, bool UseInlineStorage1, typename U, bool UseInlineStorage2>
COW_NODISCARD constexpr bool operator>=(
	const optional<T, UseInlineStorage1>& lhs, const optional<U, UseInlineStorage2>& rhs)
{
	if (!rhs)
		return true;

	if (!lhs)
		return false;

	return *lhs >= * rhs;
}

// ### comparison with nullopt

template<typename T, bool UseInlineStorage>
COW_NODISCARD constexpr bool operator==(const optional<T, UseInlineStorage>& lhs, nullopt_t) noexcept
{
	return !lhs;
}

template<typename T, bool UseInlineStorage>
COW_NODISCARD constexpr bool operator==(nullopt_t, const optional<T, UseInlineStorage>& rhs) noexcept
{
	return !rhs;
}

template<typename T, bool UseInlineStorage>
COW_NODISCARD constexpr bool operator!=(const optional<T, UseInlineStorage>& lhs, nullopt_t) noexcept
{
	return static_cast<bool>(lhs);
}

template<typename T, bool UseInlineStorage>
COW_NODISCARD constexpr bool operator!=(nullopt_t, const optional<T, UseInlineStorage>& rhs) noexcept
{
	return static_cast<bool>(rhs);
}

template<typename T, bool UseInlineStorage>
COW_NODISCARD constexpr bool operator<(const optional<T, UseInlineStorage>&, nullopt_t) noexcept
{
	return false;
}

template<typename T, bool UseInlineStorage>
COW_NODISCARD constexpr bool operator<(nullopt_t, const optional<T, UseInlineStorage>& rhs) noexcept
{
	return static_cast<bool>(rhs);
}

template<typename T, bool UseInlineStorage>
COW_NODISCARD constexpr bool operator<=(const optional<T, UseInlineStorage>& lhs, nullopt_t) noexcept
{
	return !lhs;
}

template<typename T, bool UseInlineStorage>
COW_NODISCARD constexpr bool operator<=(nullopt_t, const optional<T, UseInlineStorage>&) noexcept
{
	return true;
}

template<typename T, bool UseInlineStorage>
COW_NODISCARD constexpr bool operator>(const optional<T, UseInlineStorage>& lhs, nullopt_t) noexcept
{
	return static_cast<bool>(lhs);
}

template<typename T, bool UseInlineStorage>
COW_NODISCARD constexpr bool operator>(nullopt_t, const optional<T, UseInlineStorage>&) noexcept
{
	return false;
}

template<typename T, bool UseInlineStorage>
COW_NODISCARD constexpr bool operator>=(const optional<T, UseInlineStorage>&, nullopt_t) noexcept
{
	return true;
}

template<typename T, bool UseInlineStorage>
COW_NODISCARD constexpr bool operator>=(nullopt_t, const optional<T, UseInlineStorage>& rhs) noexcept
{
	return !rhs;
}

// ### comparison with T

template<typename T, bool UseInlineStorage, typename U>
COW_NODISCARD constexpr bool operator==(const optional<T, UseInlineStorage>& lhs, const U& rhs)
{
	return static_cast<bool>(lhs) ? *lhs == rhs : false;
}

template<typename T, bool UseInlineStorage, typename U>
COW_NODISCARD constexpr bool operator==(const U& lhs, const optional<T, UseInlineStorage>& rhs)
{
	return static_cast<bool>(rhs) ? lhs == *rhs : false;
}

template<typename T, bool UseInlineStorage, typename U>
COW_NODISCARD constexpr bool operator!=(const optional<T, UseInlineStorage>& lhs, const U& rhs)
{
	return static_cast<bool>(lhs) ? *lhs != rhs : true;
}

template<typename T, bool UseInlineStorage, typename U>
COW_NODISCARD constexpr bool operator!=(const U& lhs, const optional<T, UseInlineStorage>& rhs)
{
	return static_cast<bool>(rhs) ? lhs != *rhs : true;
}

template<typename T, bool UseInlineStorage, typename U>
COW_NODISCARD constexpr bool operator<(const optional<T, UseInlineStorage>& lhs, const U& rhs)
{
	return static_cast<bool>(lhs) ? *lhs < rhs : true;
}

template<typename T, bool UseInlineStorage, typename U>
COW_NODISCARD constexpr bool operator<(const U& lhs, const optional<T, UseInlineStorage>& rhs)
{
	return static_cast<bool>(rhs) ? lhs < *rhs : false;
}

template<typename T, bool UseInlineStorage, typename U>
COW_NODISCARD constexpr bool operator<=(const optional<T, UseInlineStorage>& lhs, const U& rhs)
{
	return static_cast<bool>(lhs) ? *lhs <= rhs : true;
}

template<typename T, bool UseInlineStorage, typename U>
COW_NODISCARD constexpr bool operator<=(const U& lhs, const optional<T, UseInlineStorage>& rhs)
{
	return static_cast<bool>(rhs) ? lhs <= *rhs : false;
}

template<typename T, bool UseInlineStorage, typename U>
COW_NODISCARD constexpr bool operator>(const optional<T, UseInlineStorage>& lhs, const U& rhs)
{
	return static_cast<bool>(lhs) ? *lhs > rhs : false;
}

template<typename T, bool UseInlineStorage, typename U>
COW_NODISCARD constexpr bool operator>(const U& lhs, const optional<T, UseInlineStorage>& rhs)
{
	return static_cast<bool>(rhs) ? lhs > *rhs : true;
}

template<typename T, bool UseInlineStorage, typename U>
COW_NODISCARD constexpr bool operator>=(const optional<T, UseInlineStorage>& lhs, const U& rhs)
{
	return static_cast<bool>(lhs) ? *lhs >= rhs : false;
}

template<typename T, bool UseInlineStorage, typename U>
COW_NODISCARD constexpr bool operator>=(const U& lhs, const optional<T, UseInlineStorage>& rhs)
{
	return static_cast<bool>(rhs) ? lhs >= *rhs : true;
}

// ## specialized algorithms

template<typename T, bool UseInlineStorage = use_inline_storage_v<T>>
COW_NODISCARD constexpr optional<std::decay_t<T>, UseInlineStorage> make_optional(T&& v)
{
	return optional<std::decay_t<T>, UseInlineStorage>(std::forward<T>(v));
}

template<typename T, bool UseInlineStorage = use_inline_storage_v<T>, typename...Args>
COW_NODISCARD constexpr optional<T, UseInlineStorage> make_optional(Args&&... args)
{
	return optional<T, UseInlineStorage>(in_place, std::forward<Args>(args)...);
}

template<typename T, bool UseInlineStorage = use_inline_storage_v<T>, typename U, typename... Args>
COW_NODISCARD constexpr optional<T, UseInlineStorage> make_optional(
	std::initializer_list<U> ilist, Args&&... args)
{
	return optional<T, UseInlineStorage>(in_place, ilist, std::forward<Args>(args)...);
}

} // namespace cow

namespace std {

template<typename T, bool UseInlineStorage>
struct hash<cow::optional<T, UseInlineStorage>> {
	static_assert(
		std::is_default_constructible<std::hash<std::remove_const_t<T>>>::value, "For T must be declared hash");

	COW_NODISCARD std::size_t operator()(const cow::optional<T, UseInlineStorage>& co) const noexcept
	{
		return co ? hash<std::remove_const_t<T>>()(*co) : 0;
	}
};

} // namespace std
