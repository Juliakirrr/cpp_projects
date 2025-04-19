#include "s21_matrix_tests.h"

TEST(s21_determinant_test, Valid_1) {
  S21Matrix matrix(1, 1);
  matrix(0, 0) = -2.12345;
  ASSERT_EQ(matrix.Determinant(), -2.12345);
}

TEST(s21_determinant_test, Valid_2) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 5;
  matrix(0, 1) = 7;
  matrix(1, 0) = -4;
  matrix(1, 1) = 1;
  ASSERT_EQ(matrix.Determinant(), 33);
}

TEST(s21_determinant_test, Valid_3) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 5, matrix(0, 1) = 7, matrix(0, 2) = 1, matrix(1, 0) = -4,
            matrix(1, 1) = 1, matrix(1, 2) = 0, matrix(2, 0) = 2,
            matrix(2, 1) = 0, matrix(2, 2) = 3;
  ASSERT_EQ(matrix.Determinant(), 97);
}

TEST(s21_determinant_test, Valid_4) {
  S21Matrix matrix(4, 4);
  matrix(0, 0) = 3, matrix(0, 1) = -3, matrix(0, 2) = -5, matrix(0, 3) = 8,
            matrix(1, 0) = -3, matrix(1, 1) = 2, matrix(1, 2) = 4,
            matrix(1, 3) = -6, matrix(2, 0) = 2, matrix(2, 1) = -5,
            matrix(2, 2) = -7, matrix(2, 3) = 5, matrix(3, 0) = -4,
            matrix(3, 1) = 3, matrix(3, 2) = 5, matrix(3, 3) = -6;
  double a = matrix.Determinant();
  int b = round(a);
  ASSERT_EQ(b, 18);
}

TEST(s21_determinant_test, Fail_1) {
  S21Matrix matrix;
  ASSERT_THROW(matrix.Determinant(), std::length_error);
}

TEST(s21_determinant_test, Fail_2) {
  S21Matrix matrix(2, 3);
  ASSERT_THROW(matrix.Determinant(), std::length_error);
}