#include "s21_matrix_tests.h"

TEST(s21_inverse_matrix_test, Valid_1) {
  S21Matrix matrix(3, 3), result(3, 3);
  matrix(0, 0) = 2, matrix(0, 1) = 5, matrix(0, 2) = 7, matrix(1, 0) = 6,
            matrix(1, 1) = 3, matrix(1, 2) = 4, matrix(2, 0) = 5,
            matrix(2, 1) = -2, matrix(2, 2) = -3;
  result(0, 0) = 1, result(0, 1) = -1, result(0, 2) = 1, result(1, 0) = -38,
            result(1, 1) = 41, result(1, 2) = -34, result(2, 0) = 27,
            result(2, 1) = -29, result(2, 2) = 24;
  ASSERT_EQ(true, matrix.InverseMatrix().EqMatrix(result));
}

TEST(s21_inverse_matrix_test, Valid_2) {
  S21Matrix matrix(2, 2), result(2, 2);
  matrix(0, 0) = 1, matrix(0, 1) = 2, matrix(1, 0) = 3, matrix(1, 1) = 4;
  result(0, 0) = -2, result(0, 1) = 1, result(1, 0) = 1.5, result(1, 1) = -0.5;
  ASSERT_EQ(true, matrix.InverseMatrix().EqMatrix(result));
}

TEST(s21_inverse_matrix_test, Valid_3) {
  S21Matrix matrix(1, 1);
  matrix(0, 0) = 2;
  ASSERT_EQ(matrix.InverseMatrix()(0, 0), 0.5);
}

TEST(s21_inverse_matrix_test, Fail_1) {
  S21Matrix matrix;
  ASSERT_THROW(matrix.InverseMatrix(), std::length_error);
}

TEST(s21_inverse_matrix_test, Fail_2) {
  S21Matrix matrix(2, 3);
  ASSERT_THROW(matrix.InverseMatrix(), std::length_error);
}

TEST(s21_inverse_matrix_test, Fail_3) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1, matrix(0, 1) = 1, matrix(1, 0) = 1, matrix(1, 1) = 1;
  ASSERT_THROW(matrix.InverseMatrix(), std::length_error);
}