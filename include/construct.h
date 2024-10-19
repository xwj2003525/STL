#pragma once

template <class T1, class T2> inline void construct(T1 *p, const T2 &arg) {
  // placement new
  // 只构造，不分配内存
  new (p) T1(arg);
}

template <class T> inline void destroy(T *p) { p->~T(); }

// TODO
