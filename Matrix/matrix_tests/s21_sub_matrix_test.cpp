#include "s21_matrix_tests.h"

TEST(s21_sub_matrix_test, Valid_Sub_1) {
  S21Matrix matrix1(3, 3), matrix2(3, 3), matrix3(3, 3);
  fill(&matrix1, 3, 3);
  fill(&matrix2, 3, 3);
  matrix1.SubMatrix(matrix2);
  ASSERT_EQ(true, matrix1.EqMatrix(matrix3));
}

TEST(s21_sub_matrix_test, Valid_Sub_2) {
  S21Matrix matrix1(3, 3), matrix2(3, 3), matrix3(3, 3);
  fill(&matrix1, 3, 3);
  fill(&matrix2, 2, 2);
  fill(&matrix3, 1, 1);
  matrix1.SubMatrix(matrix2);
  ASSERT_EQ(true, matrix1.EqMatrix(matrix3));
}

TEST(s21_sub_matrix_test, Fail_Sub_1) {
  S21Matrix matrix1(3, 2), matrix2(3, 3);
  ASSERT_THROW(matrix2.SubMatrix(matrix1), std::length_error);
}

TEST(s21_sub_matrix_test, Fail_Sub_2) {
  S21Matrix matrix1(2, 3), matrix2(3, 3);
  ASSERT_THROW(matrix2.SubMatrix(matrix1), std::length_error);
}

TEST(s21_sub_matrix_test, Sub_Operator) {
  S21Matrix matrix1(3, 3), matrix2(3, 3), matrix3(3, 3);
  fill(&matrix1, 3, 3);
  fill(&matrix2, 3, 3);
  matrix1 = matrix1 - matrix2;
  ASSERT_EQ(true, matrix1.EqMatrix(matrix3));
}

TEST(s21_sub_matrix_test, Sub_Assignment_Operator) {
  S21Matrix matrix1(3, 3), matrix2(3, 3), matrix3(3, 3);
  fill(&matrix1, 3, 3);
  fill(&matrix2, 3, 3);
  matrix1 -= matrix2;
  ASSERT_EQ(true, matrix1.EqMatrix(matrix3));
}