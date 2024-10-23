#pragma once

#include "type.h"

namespace tt {

// is const
template <typename... Arg> struct is_const : tt::false_type {
  static_assert(sizeof...(Arg) != 0, "is_const<> is invalid");
};

template <typename T, typename... Args>
struct is_const<T, Args...> : false_type {};

template <typename T, typename... Args>
struct is_const<const T, Args...> : is_const<Args...> {};

template <typename T> struct is_const<const T> : true_type {};

// is same
template <typename... Args> struct is_same : tt::false_type {
  static_assert(sizeof...(Args) >= 2, "is_same<T1,T2> at lease two type");
};

template <typename T> struct is_same<T, T> : tt::true_type {};

template <typename T, typename U, typename... Args>
struct is_same<T, U, Args...> : false_type {};

template <typename T, typename... Args>
struct is_same<T, T, Args...> : is_same<T, Args...> {};

// is volatile
template <typename... Args> struct is_volatile : tt::false_type {
  static_assert(sizeof...(Args) >= 1, "is_volatile<T> at lease one type");
};

template <typename T, typename... Args>
struct is_volatile<T, Args...> : tt::false_type {};

template <typename T, typename... Args>
struct is_volatile<volatile T, Args...> : is_volatile<Args...> {};

template <typename T> struct is_volatile<volatile T> : tt::true_type {};

// is renference
template <typename... Args> struct is_reference : false_type {
  static_assert(sizeof...(Args) >= 1, "is_reference<T> at lease one type");
};

template <typename T, typename... Args>
struct is_reference<T &, Args...> : is_reference<Args...> {};

template <typename T> struct is_reference<T &> : true_type {};

template <typename T, typename... Args>
struct is_reference<T, Args...> : false_type {};

// is point
template <typename... Args> struct is_point : false_type {
  static_assert(sizeof...(Args) >= 1, "is_point<T> at lease one type");
};

template <typename T, typename... Args>
struct is_point<T *, Args...> : is_point<Args...> {};

template <typename T> struct is_point<T *> : true_type {};

template <typename T, typename... Args>
struct is_point<T, Args...> : false_type {};

//

template <typename... T>
inline constexpr bool is_const_v = tt::is_const<T...>::value;

template <typename... T>
inline constexpr bool is_same_v = tt::is_same<T...>::value;

template <typename... T>
inline constexpr bool is_volatile_v = tt::is_volatile<T...>::value;

template <typename... T>
inline constexpr bool is_reference_v = tt::is_reference<T...>::value;

template <typename... T>
inline constexpr bool is_point_v = tt::is_point<T...>::value;
}; // namespace tt
