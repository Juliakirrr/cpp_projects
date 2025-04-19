#include "s21_matrix_tests.h"

TEST(s21_cacl_complements_test, Valid_1) {
  S21Matrix matrix(3, 3), result(3, 3);
  matrix(0, 0) = 1, matrix(0, 1) = 2, matrix(0, 2) = 3, matrix(1, 0) = 0,
            matrix(1, 1) = 4, matrix(1, 2) = 2, matrix(2, 0) = 5,
            matrix(2, 1) = 2, matrix(2, 2) = 1;
  result(0, 0) = 0, result(0, 1) = 10, result(0, 2) = -20, result(1, 0) = 4,
            result(1, 1) = -14, result(1, 2) = 8, result(2, 0) = -8,
            result(2, 1) = -2, result(2, 2) = 4;
  ASSERT_EQ(true, matrix.CalcComplements().EqMatrix(result));
}

TEST(s21_cacl_complements_test, Valid_2) {
  S21Matrix matrix(2, 2), result(2, 2);
  matrix(0, 0) = 1, matrix(0, 1) = -5, matrix(1, 0) = 3, matrix(1, 1) = -4;
  result(0, 0) = -4, result(0, 1) = -3, result(1, 0) = 5, result(1, 1) = 1;
  ASSERT_EQ(true, matrix.CalcComplements().EqMatrix(result));
}

TEST(s21_cacl_complements_test, Fail_1) {
  S21Matrix matrix;
  ASSERT_THROW(matrix.CalcComplements(), std::length_error);
}

TEST(s21_cacl_complements_test, Fail_2) {
  S21Matrix matrix(2, 3);
  ASSERT_THROW(matrix.CalcComplements(), std::length_error);
}