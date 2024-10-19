#pragma once

#include "constant.h"

namespace tt {

template <typename T> struct is_const : false_type {};

template <typename T> struct is_const<const T> : true_type {};

}; // namespace tt
