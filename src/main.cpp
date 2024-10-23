#include "../include/traits/remove.h" // ???滻Ϊ??????????????ʵ???ļ???
#include <iostream>
#include <type_traits>

int main() {
  // ??֤ remove_const_t
  static_assert(
      std::is_same_v<tt::remove_const_t<int>, std::remove_const_t<int>>,
      "remove_const_t<int> mismatch");
  static_assert(std::is_same_v<tt::remove_const_t<volatile int>,
                               std::remove_const_t<volatile int>>,
                "remove_const_t<volatile int> mismatch");
  static_assert(std::is_same_v<tt::remove_const_t<const int>,
                               std::remove_const_t<const int>>,
                "remove_const_t<const int> mismatch");
  static_assert(
      std::is_same_v<tt::remove_const_t<int &>, std::remove_const_t<int &>>,
      "remove_const_t<int&> mismatch");
  static_assert(std::is_same_v<tt::remove_const_t<const int &>,
                               std::remove_const_t<const int &>>,
                "remove_const_t<const int&> mismatch");
  static_assert(std::is_same_v<tt::remove_const_t<volatile int &>,
                               std::remove_const_t<volatile int &>>,
                "remove_const_t<volatile int&> mismatch");
  static_assert(std::is_same_v<tt::remove_const_t<const volatile int &>,
                               std::remove_const_t<const volatile int &>>,
                "remove_const_t<const volatile int&> mismatch");
  static_assert(
      std::is_same_v<tt::remove_const_t<int *>, std::remove_const_t<int *>>,
      "remove_const_t<int*> mismatch");
  static_assert(std::is_same_v<tt::remove_const_t<const int *>,
                               std::remove_const_t<const int *>>,
                "remove_const_t<const int*> mismatch");
  static_assert(std::is_same_v<tt::remove_const_t<int *const>,
                               std::remove_const_t<int *const>>,
                "remove_const_t<int* const> mismatch");
  static_assert(std::is_same_v<tt::remove_const_t<const int *const>,
                               std::remove_const_t<const int *const>>,
                "remove_const_t<const int* const> mismatch");

  // ??֤ remove_volatile_t
  static_assert(
      std::is_same_v<tt::remove_volatile_t<int>, std::remove_volatile_t<int>>,
      "remove_volatile_t<int> mismatch");
  static_assert(std::is_same_v<tt::remove_volatile_t<const int>,
                               std::remove_volatile_t<const int>>,
                "remove_volatile_t<const int> mismatch");
  static_assert(std::is_same_v<tt::remove_volatile_t<volatile int>,
                               std::remove_volatile_t<volatile int>>,
                "remove_volatile_t<volatile int> mismatch");
  static_assert(std::is_same_v<tt::remove_volatile_t<int &>,
                               std::remove_volatile_t<int &>>,
                "remove_volatile_t<int&> mismatch");
  static_assert(std::is_same_v<tt::remove_volatile_t<const int &>,
                               std::remove_volatile_t<const int &>>,
                "remove_volatile_t<const int&> mismatch");
  static_assert(std::is_same_v<tt::remove_volatile_t<volatile int &>,
                               std::remove_volatile_t<volatile int &>>,
                "remove_volatile_t<volatile int&> mismatch");
  static_assert(std::is_same_v<tt::remove_volatile_t<const volatile int &>,
                               std::remove_volatile_t<const volatile int &>>,
                "remove_volatile_t<const volatile int&> mismatch");

  // ??֤ remove_reference_t
  static_assert(
      std::is_same_v<tt::remove_reference_t<int>, std::remove_reference_t<int>>,
      "remove_reference_t<int> mismatch");
  static_assert(std::is_same_v<tt::remove_reference_t<int &>,
                               std::remove_reference_t<int &>>,
                "remove_reference_t<int&> mismatch");
  static_assert(std::is_same_v<tt::remove_reference_t<const int &>,
                               std::remove_reference_t<const int &>>,
                "remove_reference_t<const int&> mismatch");
  static_assert(std::is_same_v<tt::remove_reference_t<volatile int &>,
                               std::remove_reference_t<volatile int &>>,
                "remove_reference_t<volatile int&> mismatch");
  static_assert(std::is_same_v<tt::remove_reference_t<int &&>,
                               std::remove_reference_t<int &&>>,
                "remove_reference_t<int&&> mismatch");
  static_assert(std::is_same_v<tt::remove_reference_t<const int &&>,
                               std::remove_reference_t<const int &&>>,
                "remove_reference_t<const int&&> mismatch");

  // ??֤ remove_pointer_t
  static_assert(
      std::is_same_v<tt::remove_pointer_t<int>, std::remove_pointer_t<int>>,
      "remove_pointer_t<int> mismatch");
  static_assert(
      std::is_same_v<tt::remove_pointer_t<int *>, std::remove_pointer_t<int *>>,
      "remove_pointer_t<int*> mismatch");
  static_assert(std::is_same_v<tt::remove_pointer_t<const int *>,
                               std::remove_pointer_t<const int *>>,
                "remove_pointer_t<const int*> mismatch");
  static_assert(std::is_same_v<tt::remove_pointer_t<int *const>,
                               std::remove_pointer_t<int *const>>,
                "remove_pointer_t<int* const> mismatch");
  static_assert(std::is_same_v<tt::remove_pointer_t<const int *const>,
                               std::remove_pointer_t<const int *const>>,
                "remove_pointer_t<const int* const> mismatch");

  // ??֤ remove_array_t
  // static_assert(std::is_same_v<tt::remove_array_t<int>,
  // std::remove_array_t<int>>, "remove_array_t<int> mismatch");
  // static_assert(std::is_same_v<tt::remove_array_t<int[5]>,
  // std::remove_array_t<int[5]>>, "remove_array_t<int[5]> mismatch");
  // static_assert(std::is_same_v<tt::remove_array_t<int[]>,
  // std::remove_array_t<int[]>>, "remove_array_t<int[]> mismatch");

  // ??֤ remove_cv_t
  static_assert(std::is_same_v<tt::remove_cv_t<int>, std::remove_cv_t<int>>,
                "remove_cv_t<int> mismatch");
  static_assert(
      std::is_same_v<tt::remove_cv_t<const int>, std::remove_cv_t<const int>>,
      "remove_cv_t<const int> mismatch");
  static_assert(std::is_same_v<tt::remove_cv_t<volatile int>,
                               std::remove_cv_t<volatile int>>,
                "remove_cv_t<volatile int> mismatch");
  static_assert(std::is_same_v<tt::remove_cv_t<const volatile int>,
                               std::remove_cv_t<const volatile int>>,
                "remove_cv_t<const volatile int> mismatch");
  static_assert(std::is_same_v<tt::remove_cv_t<int &>, std::remove_cv_t<int &>>,
                "remove_cv_t<int&> mismatch");
  static_assert(std::is_same_v<tt::remove_cv_t<const int &>,
                               std::remove_cv_t<const int &>>,
                "remove_cv_t<const int&> mismatch");
  static_assert(std::is_same_v<tt::remove_cv_t<volatile int &>,
                               std::remove_cv_t<volatile int &>>,
                "remove_cv_t<volatile int&> mismatch");
  static_assert(std::is_same_v<tt::remove_cv_t<const volatile int &>,
                               std::remove_cv_t<const volatile int &>>,
                "remove_cv_t<const volatile int&> mismatch");

  static_assert(std::is_same<tt::remove_rp_t<int &>, int>::value,
                "Failed for int&");
  static_assert(std::is_same<tt::remove_rp_t<const int &>, const int>::value,
                "Failed for const int&");
  static_assert(
      std::is_same<tt::remove_rp_t<volatile int &>, volatile int>::value,
      "Failed for volatile int&");
  static_assert(std::is_same<tt::remove_rp_t<int *>, int>::value,
                "Failed for int*");
  static_assert(std::is_same<tt::remove_rp_t<const int *>, const int>::value,
                "Failed for const int*");
  static_assert(std::is_same<tt::remove_rp_t<int **>, int *>::value,
                "Failed for int**");
  static_assert(std::is_same<tt::remove_rp_t<int *&>, int>::value,
                "Failed for int*&");
  static_assert(std::is_same<tt::remove_rp_t<const int *&>, const int>::value,
                "Failed for const int*&");
  static_assert(std::is_same<tt::remove_rp_t<int &&>, int>::value,
                "Failed for int&&");
  static_assert(std::is_same<tt::remove_rp_t<int ***>, int **>::value,
                "Failed for int***");

  // ???? remove_cvrp_t
  static_assert(std::is_same<tt::remove_cvrp_t<int &>, int>::value,
                "Failed for int&");
  static_assert(std::is_same<tt::remove_cvrp_t<const int &>, int>::value,
                "Failed for const int&");
  static_assert(std::is_same<tt::remove_cvrp_t<volatile int>, int>::value,
                "Failed for volatile int");
  static_assert(std::is_same<tt::remove_cvrp_t<const volatile int>, int>::value,
                "Failed for const volatile int");
  static_assert(std::is_same<tt::remove_cvrp_t<int *&>, int>::value,
                "Failed for int*&");
  static_assert(std::is_same<tt::remove_cvrp_t<const int *&>, int>::value,
                "Failed for const int*&");
  static_assert(std::is_same<tt::remove_cvrp_t<int **>, int *>::value,
                "Failed for int**");
  static_assert(
      std::is_same<tt::remove_cvrp_t<const int **>, const int *>::value,
      "Failed for const int**");
  static_assert(std::is_same<tt::remove_cvrp_t<int ***>, int **>::value,
                "Failed for int***");
  static_assert(
      std::is_same<tt::remove_cvrp_t<const int ***>, const int **>::value,
      "Failed for const int***");

  // ??ӡ??֤ͨ??????Ϣ
  std::cout << "All tests passed!" << std::endl;
  return 0;
}
