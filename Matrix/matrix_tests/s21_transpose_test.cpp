#include "s21_matrix_tests.h"

TEST(s21_transpose_test, Valid_1) {
  S21Matrix matrix(2, 2);
  fill(&matrix, 2, 2);
  S21Matrix transposed = matrix.Transpose();
  ASSERT_EQ(transposed.getRows(), 2);
  ASSERT_EQ(transposed.getCols(), 2);
  ASSERT_EQ(transposed(0, 0), 2);
  ASSERT_EQ(transposed(0, 1), 6);
  ASSERT_EQ(transposed(1, 0), 4);
  ASSERT_EQ(transposed(1, 1), 8);
}

TEST(s21_transpose_test, Valid_2) {
  S21Matrix matrix(2, 3);
  fill(&matrix, 2, 2);
  S21Matrix transposed = matrix.Transpose();
  ASSERT_EQ(transposed.getRows(), 3);
  ASSERT_EQ(transposed.getCols(), 2);
  ASSERT_EQ(transposed(0, 0), 2);
  ASSERT_EQ(transposed(0, 1), 8);
  ASSERT_EQ(transposed(1, 0), 4);
  ASSERT_EQ(transposed(1, 1), 10);
  ASSERT_EQ(transposed(2, 0), 6);
  ASSERT_EQ(transposed(2, 1), 12);
}

TEST(s21_transpose_test, Valid_3) {
  S21Matrix matrix(3, 2);
  fill(&matrix, 2, 2);
  S21Matrix transposed = matrix.Transpose();
  ASSERT_EQ(transposed.getRows(), 2);
  ASSERT_EQ(transposed.getCols(), 3);
  ASSERT_EQ(transposed(0, 0), 2);
  ASSERT_EQ(transposed(0, 1), 6);
  ASSERT_EQ(transposed(0, 2), 10);
  ASSERT_EQ(transposed(1, 0), 4);
  ASSERT_EQ(transposed(1, 1), 8);
  ASSERT_EQ(transposed(1, 2), 12);
}

TEST(s21_transpose_test, Valid_4) {
  S21Matrix matrix(1, 4);
  fill(&matrix, 2, 2);
  S21Matrix transposed = matrix.Transpose();
  ASSERT_EQ(transposed.getRows(), 4);
  ASSERT_EQ(transposed.getCols(), 1);
  ASSERT_EQ(transposed(0, 0), 2);
  ASSERT_EQ(transposed(1, 0), 4);
  ASSERT_EQ(transposed(2, 0), 6);
  ASSERT_EQ(transposed(3, 0), 8);
}

TEST(s21_transpose_test, Valid_5) {
  S21Matrix matrix(4, 1);
  fill(&matrix, 2, 2);
  S21Matrix transposed = matrix.Transpose();
  ASSERT_EQ(transposed.getRows(), 1);
  ASSERT_EQ(transposed.getCols(), 4);
  ASSERT_EQ(transposed(0, 0), 2);
  ASSERT_EQ(transposed(0, 1), 4);
  ASSERT_EQ(transposed(0, 2), 6);
  ASSERT_EQ(transposed(0, 3), 8);
}

TEST(s21_transpose_test, Fail_1) {
  S21Matrix matrix;
  ASSERT_THROW(matrix.Transpose(), std::length_error);
}