#include "../include/traits/is_same.h"
#include "../include/traits/remove.h"

#include <iostream>
using namespace tt; // 使用你的命名空间

int main() {
  int a;
  int &b = a;
  int *c = &a;
  const int d = a;
  int volatile e = a;
  int f[5];

  // 测试 remove_const
  static_assert(is_same<remove_const<const int>::type, int>::value,
                "remove_const failed");
  static_assert(is_same<remove_const<int>::type, int>::value,
                "remove_const failed");

  // 测试 remove_volatile
  static_assert(is_same<remove_volatile<int volatile>::type, int>::value,
                "remove_volatile failed");
  static_assert(is_same<remove_volatile<int>::type, int>::value,
                "remove_volatile failed");

  // 测试 remove_reference
  static_assert(is_same<remove_reference<int &>::type, int>::value,
                "remove_reference failed");
  static_assert(is_same<remove_reference<int &&>::type, int>::value,
                "remove_reference failed");
  static_assert(is_same<remove_reference<int>::type, int>::value,
                "remove_reference failed");

  // 测试 remove_pointer
  static_assert(is_same<remove_pointer<int *>::type, int>::value,
                "remove_pointer failed");
  static_assert(is_same<remove_pointer<int>::type, int>::value,
                "remove_pointer failed");

  // 测试 remove_array
  static_assert(is_same<remove_array<int[]>::type, int>::value,
                "remove_array failed");
  static_assert(is_same<remove_array<int[5]>::type, int>::value,
                "remove_array failed");

  // 测试 remove_arrays
  static_assert(is_same<remove_arrays<int[]>::type, int>::value,
                "remove_arrays failed");
  static_assert(is_same<remove_arrays<int[5]>::type, int>::value,
                "remove_arrays failed");
  static_assert(is_same<remove_arrays<int[5][10]>::type, int>::value,
                "remove_arrays failed");

  // 测试 remove_cv
  static_assert(is_same<remove_cv<const volatile int>::type, int>::value,
                "remove_cv failed");
  static_assert(is_same<remove_cv<int>::type, int>::value, "remove_cv failed");

  // 测试 remove_rp
  static_assert(is_same<remove_rp<int *>::type, int>::value,
                "remove_rp failed");
  static_assert(is_same<remove_rp<int &>::type, int>::value,
                "remove_rp failed");

  // 测试 remove_cvrp
  //static_assert(is_same<remove_cvrp<const int *&>::type, int>::value,
  //              "remove_cvrp failed");
  static_assert(is_same<remove_cvrp<int volatile &>::type, int>::value,
                "remove_cvrp failed");

  return 0;
}
