#pragma once
namespace tt {

 // all these remove , only remove once like int ** remove_point -> int *

template <typename T> struct remove_const { using type = T; };
template <typename T> struct remove_const<const T> { using type = T; };

template <typename T> struct remove_volatile { using type = T; };
template <typename T> struct remove_volatile<T volatile> { using type = T; };

template <typename T> struct remove_reference { using type = T; };
template <typename T> struct remove_reference<T &> { using type = T; };
template <typename T> struct remove_reference<T &&> { using type = T; };

template <typename T> struct remove_pointer { using type = T; };
template <typename T> struct remove_pointer<T *> { using type = T; };
template <typename T> struct remove_pointer<T *const> { using type = T; };

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
      typename remove_pointer<typename remove_reference<T>::type>::type;
};

template <typename T> struct remove_cvrp {
  using type = typename remove_cv<typename remove_rp<T>::type>::type;
};

template <typename T> using remove_const_t = typename remove_const<T>::type;

template <typename T>
using remove_volatile_t = typename remove_volatile<T>::type;

template <typename T>
using remove_reference_t = typename remove_reference<T>::type;

template <typename T> using remove_pointer_t = typename remove_pointer<T>::type;

template <typename T> using remove_array_t = typename remove_array<T>::type;

template <typename T> using remove_arrays_t = typename remove_arrays<T>::type;

template <typename T> using remove_cv_t = typename remove_cv<T>::type;

template <typename T> using remove_rp_t = typename remove_rp<T>::type;

template <typename T> using remove_cvrp_t = typename remove_cvrp<T>::type;
}; // namespace tt
