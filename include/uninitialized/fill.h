#pragma once

#include "../construct.h"

template <class ForwardIter, class T>
void uninitialized_fill(ForwardIter first, ForwardIter last, const T &x) {
  return _uninitialized_fill(first, last, x, value_type(first));
}

template <class ForwardIter, class T, class T1>
inline void _uninitialized_fill(ForwardIter first, ForwardIter last, const T &x,
                                T1 *) {
  typedef typename __type_traits<T1>::is_POD_type is_POD;
  return _uninitialized_fill_aux(first, last, x, is_POD());
}

template <class ForwardIter, class T>
inline void _uninitialized_fill_aux(ForwardIter first, ForwardIter last,
                                    const T &x, __true_type) {
  return fill(first, last, x);
}

template <class ForwardIter, class T>
inline void _uninitialized_fill_aux(ForwardIter first, ForwardIter last,
                                    const T &x, __false_type) {
  ForwardIter cur = first;
  for (; cur != last; ++cur) {
    construct(&*cur, x);
  }

  return cur;
}
