#include "s21_matrix_tests.h"

TEST(s21_accessor_test, Valid_1) {
  S21Matrix matrix(2, 2);
  matrix(1, 1) = 5;
  ASSERT_EQ(matrix(1, 1), 5);
}

TEST(s21_accessor_test, Fail_1) {
  S21Matrix matrix(2, 2);
  ASSERT_THROW(matrix(5, 0), std::length_error);
}

TEST(s21_accessor_test, Fail_2) {
  S21Matrix matrix(2, 2);
  ASSERT_THROW(matrix(0, 5), std::length_error);
}

TEST(s21_accessor_test, Fail_3) {
  S21Matrix matrix(2, 2);
  ASSERT_THROW(matrix(-1, 0), std::length_error);
}

TEST(s21_accessor_test, Fail_4) {
  S21Matrix matrix(2, 2);
  ASSERT_THROW(matrix(0, -1), std::length_error);
}

TEST(s21_accessor_test, Valid_Const_1) {
  const S21Matrix matrix(2, 2);
  matrix(1, 1) = 5;
  ASSERT_EQ(matrix(1, 1), 5);
}

TEST(s21_accessor_test, Fail_Const_1) {
  const S21Matrix matrix(2, 2);
  ASSERT_THROW(matrix(5, 0), std::length_error);
}

TEST(s21_accessor_test, Fail_Const_2) {
  const S21Matrix matrix(2, 2);
  ASSERT_THROW(matrix(0, 5), std::length_error);
}

TEST(s21_accessor_test, Fail_Const_3) {
  const S21Matrix matrix(2, 2);
  ASSERT_THROW(matrix(-1, 0), std::length_error);
}

TEST(s21_accessor_test, Fail_Const_4) {
  const S21Matrix matrix(2, 2);
  ASSERT_THROW(matrix(0, -1), std::length_error);
}

TEST(s21_mutator_test, Valid_Set_Rows_1) {
  S21Matrix matrix(2, 3);
  fill(&matrix, 2, 2);
  matrix.SetRows(4);
  ASSERT_EQ(matrix.getRows(), 4);
  ASSERT_EQ(matrix.getCols(), 3);
  ASSERT_EQ(matrix(2, 0), 0);
}

TEST(s21_mutator_test, Valid_Set_Rows_2) {
  S21Matrix matrix(2, 3);
  fill(&matrix, 2, 2);
  matrix.SetRows(2);
  ASSERT_EQ(matrix.getRows(), 2);
  ASSERT_EQ(matrix.getCols(), 3);
}

TEST(s21_mutator_test, Valid_Set_Rows_3) {
  S21Matrix matrix(3, 3);
  fill(&matrix, 2, 2);
  matrix.SetRows(1);
  ASSERT_EQ(matrix.getRows(), 1);
  ASSERT_EQ(matrix.getCols(), 3);
}

TEST(s21_mutator_test, Fail_Set_Rows_1) {
  S21Matrix matrix(2, 3);
  ASSERT_THROW(matrix.SetRows(-1), std::length_error);
}

TEST(s21_mutator_test, Valid_Set_Cols_1) {
  S21Matrix matrix(2, 2);
  fill(&matrix, 2, 2);
  matrix.SetColumns(4);
  ASSERT_EQ(matrix.getRows(), 2);
  ASSERT_EQ(matrix.getCols(), 4);
  ASSERT_EQ(matrix(1, 3), 0);
}

TEST(s21_mutator_test, Valid_Set_Cols_2) {
  S21Matrix matrix(2, 3);
  fill(&matrix, 2, 2);
  matrix.SetColumns(3);
  ASSERT_EQ(matrix.getRows(), 2);
  ASSERT_EQ(matrix.getCols(), 3);
}

TEST(s21_mutator_test, Valid_Set_Cols_3) {
  S21Matrix matrix(3, 3);
  fill(&matrix, 2, 2);
  matrix.SetColumns(1);
  ASSERT_EQ(matrix.getRows(), 3);
  ASSERT_EQ(matrix.getCols(), 1);
}

TEST(s21_mutator_test, Fail_Set_Cols_1) {
  S21Matrix matrix(2, 3);
  ASSERT_THROW(matrix.SetColumns(-1), std::length_error);
}