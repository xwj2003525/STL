#pragma once

#include "../construct.h"

template <class InputIter, class ForwardIter>
void uninitialized_copy(InputIter first, InputIter last, ForwardIter ret) {
  return _uninitialized_copy(first, last, ret, value_type(first));
}

template <class InputIter, class ForwardIter, class T>
void _uninitialized_copy(InputIter first, InputIter last, ForwardIter ret,
                         T *) {
  typedef typename __type_traits<T>::is_POD_type is_POD;
  return _uninitialized_copy_aux(first, last, ret, is_POD());
}

template <class InputIter, class ForwardIter>
void _uninitialized_copy_aux(InputIter first, InputIter last, ForwardIter ret,
                             __true_type) {
  return copy(first, last, ret);
}

template <class InputIter, class ForwardIter>
void _uninitialized_copy_aux(InputIter first, InputIter last, ForwardIter ret,
                             __false_type) {
  ForwardIter cur = ret;
  for (; first != last; ++first, ++cur) {
    construct(&*cur, *first);
  }

  return cur;
}
