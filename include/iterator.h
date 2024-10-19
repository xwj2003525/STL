#pragma once

#include <cstddef>

struct r_iter_tag {};
struct w_iter_tag {};
struct one_iter_tag : public r_iter_tag {};
struct two_iter_tag : public one_iter_tag {};
struct random_iter_tag : public two_iter_tag {};

template <class Category, class T, class Distance = ptrdiff_t, class p = T *,
          class ref = T &>
struct iter {
  typedef Category iter_type;
  typedef T value_type;
  typedef Distance gap_type;
  typedef p pointer;
  typedef ref reference;
};

template <class Iterator> struct iter_traits {
  typedef typename Iterator::iter_type iter_type;
  typedef typename Iterator::value_type value_type;
  typedef typename Iterator::gap_type gap_type;
  typedef typename Iterator::pointer pointer;
  typedef typename Iterator::reference reference;
};

// 原生指针
template <class T> struct iter_traits<T *> {
  typedef random_iter_tag iter_type;
  typedef T value_type;
  typedef T *pointer;
  typedef T &reference;
  typedef ptrdiff_t gap_type;
};

// 原生const指针
template <class T> struct iter_traits<const T *> {
  typedef random_iter_tag iter_type;
  typedef T value_type;
  typedef T *pointer;
  typedef T &reference;
  typedef ptrdiff_t gap_type;
};

//  实例化类型·

template <class T>
inline typename iter_traits<T>::iter_type iter_type(const T &) {
  typedef typename iter_traits<T>::iter_type type;
  return type();
}

template <class T>
inline typename iter_traits<T>::gap_type gap_type(const T &) {
  return static_cast<typename iter_traits<T>::gap_type>(0);
}

template <class T>
inline typename iter_traits<T>::value_type value_type(const T &) {

  return static_cast<typename iter_traits<T>::value_type>(0);
}
