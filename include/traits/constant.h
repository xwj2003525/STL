#pragma once

namespace tt {

template <typename T, T t> struct any_constant {
  static constexpr T value = t;
  using value_type = T;
  using type = any_constant<T, t>;
};

using false_type = any_constant<bool, false>;
using true_type = any_constant<bool, true>;

}; // namespace tt
