#pragma once

#include "../construct.h"

template <class ForwardIter, class Size, class T>
void uninitialized_fill_n(ForwardIter first, Size n, const T &x) {
  return _uninitialized_fill_n(first, n, x, value_type(first));
}

template <class ForwardIter, class Size, class T, class T1>
inline void _uninitialized_fill_n(ForwardIter first, Size n, const T &x, T1 *) {
  typedef typename __type_traits<T1>::is_POD_type is_POD;
  return _uninitialized_fill_n_aux(first, n, x, is_POD());
}

template <class ForwardIter, class Size, class T>
inline void _uninitialized_fill_n_aux(ForwardIter first, Size n, const T &x,
                                      __true_type) {
  return fill_n(first, n, x);
}

template <class ForwardIter, class Size, class T>
inline void _uninitialized_fill_aux(ForwardIter first, Size n, const T &x,
                                    __false_type) {
  ForwardIter cur = first;
  for (; n > 0; --n, ++cur) {
    construct(&*cur, x);
  }

  return cur;
}
