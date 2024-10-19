#pragma once

#include "constant.h"
#include <type_traits>

namespace tt {

template <typename T, typename S> struct is_same : false_type {};

template <typename T> struct is_same<T, T> : true_type {};

}; // namespace tt
