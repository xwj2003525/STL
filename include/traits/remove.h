#pragma once
#include <cstddef>
namespace tt {

template <typename T> struct remove_const { using type = T; };
template <typename T> struct remove_const<const T> { using type = T; };

template <typename T> struct remove_volatile { using type = T; };
template <typename T> struct remove_volatile<T volatile> { using type = T; };

template <typename T> struct remove_reference { using type = T; };
template <typename T> struct remove_reference<T &> { using type = T; };
template <typename T> struct remove_reference<T &&> { using type = T; };

template <typename T> struct remove_pointer { using type = T; };
template <typename T> struct remove_pointer<T *> { using type = T; };
template <typename T> struct remove_pointer<const T *> { using type = T; };
template <typename T> struct remove_pointer<T *const> { using type = T; };
template <typename T> struct remove_pointer<const T *const> { using type = T; };

template <typename T> struct remove_array { using type = T; };
template <typename T, size_t N> struct remove_array<T[N]> { using type = T; };
template <typename T> struct remove_array<T[]> { using type = T; };

template <typename T> struct remove_arrays { using type = T; };
template <typename T> struct remove_arrays<T[]> {
  using type = typename remove_arrays<T>::type;
};
template <typename T, size_t N> struct remove_arrays<T[N]> {
  using type = typename remove_arrays<T>::type;
};

template <typename T> struct remove_cv {
  using type = typename remove_const<typename remove_volatile<T>::type>::type;
};

template <typename T> struct remove_rp {
  using type =
      typename remove_reference<typename remove_pointer<T>::type>::type;
};

// TODO 有点问题
template <typename T> struct remove_cvrp {
  using type = typename remove_cv<typename remove_rp<T>::type>::type;
};

}; // namespace tt
