#pragma once

namespace tt {

template <auto t> struct any_type {
  using T = decltype(t);
  static constexpr T value = t;

  using type = T;
  using reference = T &;
  using pointer = T *;
};

using false_type = any_type<false>;
using true_type = any_type<true>;

}; // namespace tt
