#include "s21_matrix_tests.h"

TEST(s21_constructor_test, Default_Constructor) {
  S21Matrix matrix;
  ASSERT_EQ(matrix.getRows(), 0);
  ASSERT_EQ(matrix.getCols(), 0);
  ASSERT_EQ(matrix.getMatrix(), nullptr);
}

TEST(s21_constructor_test, Param_Constructor) {
  S21Matrix matrix(2, 3);
  ASSERT_EQ(matrix.getRows(), 2);
  ASSERT_EQ(matrix.getCols(), 3);
}

TEST(s21_constructor_test, Param_Constructor_fail_1) {
  ASSERT_THROW(S21Matrix(0, 1), std::length_error);
}

TEST(s21_constructor_test, Param_Constructor_fail_2) {
  ASSERT_THROW(S21Matrix(1, 0), std::length_error);
}

TEST(s21_constructor_test, Copy_Constructor) {
  S21Matrix tmp(3, 3);
  fill(&tmp, 2, 2);
  S21Matrix matrix(tmp);
  ASSERT_EQ(matrix.getRows(), 3);
  ASSERT_EQ(matrix.getCols(), 3);
  ASSERT_EQ(true, tmp == matrix);
}

TEST(s21_constructor_test, Copy_Constructor_fail_1) {
  ASSERT_THROW(S21Matrix(S21Matrix(3, 0)), std::length_error);
}

TEST(s21_constructor_test, Copy_Constructor_fail_2) {
  ASSERT_THROW(S21Matrix(S21Matrix(0, 3)), std::length_error);
}

TEST(s21_constructor_test, Move_Constructor) {
  S21Matrix tmp(3, 3);
  fill(&tmp, 2, 2);
  S21Matrix matrix(std::move(tmp));
  ASSERT_EQ(matrix.getRows(), 3);
  ASSERT_EQ(matrix.getCols(), 3);
  ASSERT_EQ(matrix.getMatrix()[1][1], 10);
  ASSERT_EQ(tmp.getRows(), 0);
  ASSERT_EQ(tmp.getCols(), 0);
  ASSERT_EQ(tmp.getMatrix(), nullptr);
}