#pragma once

#include "..\core\custom_def.h"

_CUSTOM_BEGIN_

// ---- enable_if

template<bool B, typename T = void>
struct enable_if {};

template<typename T>
struct enable_if<true, T> {
	typedef T type;
};

template <typename T>
bool is_object() {
	return true;
}

// ---- BASE / HELPER CLASSES -----

template <typename T, T val>
struct integral_constant {
	static constexpr T value = val;
	using value_type = T;
	using type = integral_constant;

	constexpr operator value_type() const noexcept {
		return value;
	}

	constexpr value_type operator()() const noexcept {
		return value;
	}
};

template <bool B>
using bool_constant = integral_constant<bool, B>;

typedef bool_constant<true> true_type;
typedef bool_constant<false> false_type;

//---------------------------------

// ----- TYPE RELATIONSHIPS

template <typename T1, typename T2>
struct is_same : false_type {};

template <typename T>
struct is_same<T, T> : true_type {};

// -----------------------------------------------

// ----- ATTRIBUTE TRANSFORM -----

// add_const, add_cv, add_volatile
// remove_const, remove_cv, remove_volatile

// adding
template <typename T>
struct add_const {
	typedef const T type; 
};

template <typename T>
struct add_volatile {
	typedef volatile T type;
};

template <typename T>
struct add_cv {
	typedef const volatile T type;
};

// removing
template <typename T>
struct remove_const {
	typedef T type;
};
template <typename T>
struct remove_const<const T> {
	typedef T type;
};

template <typename T>
struct remove_volatile {
	typedef T type;
};
template <typename T>
struct remove_volatile<volatile T> {
	typedef T type;
};

template <typename T>
struct remove_cv {
	using type = typename remove_volatile<typename remove_const<T>::type>::type;
};


// INTEGRAL EXTENSIONS


// ----- ATTRIBUTES ------------------------------

template <typename T>
struct is_const : false_type {};
template <typename T>
struct is_const<const T> : true_type {};

template <typename T>
struct is_volatile : false_type {};
template <typename T>
struct is_volatile<volatile T> : true_type {};

template <typename T>
constexpr bool is_const_volatile_v = is_volatile<T>::value && is_const<T>::value;
template <typename T>
struct is_const_volatile : bool_constant<is_const_volatile_v<T>> {};

// ------------------------------------------------

// PRIMARY TYPE CATEGORIES

template <typename T>
constexpr bool is_void_v = is_same<void, remove_cv<T>>::value;

template <typename T>
struct is_void : bool_constant<is_void_v<T>> {};


template <typename T>
constexpr bool is_nullptr_v = is_same<nullptr_t, remove_cv<T>>::value;

template <typename T>
struct is_nullptr : bool_constant<is_nullptr_v<T>> {};


#if 0
template <typename T>
constexpr bool is_integral_v =
	is_same<>

// fundamental

template <typename T>
constexpr bool is_fundamental_v = is_arithmethic_type_v<T> || is_void_v<T> || is_nullptr_v<T>;
template <typename T>
struct is_fundamental : bool_constant<is_fundamental_v<T>> {};
#endif

template <typename T>
struct is_compound_type {};

_CUSTOM_END_