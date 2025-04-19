#include "s21_matrix_tests.h"

TEST(s21_sum_matrix_test, Valid_Sum_1) {
  S21Matrix matrix1(3, 3), matrix2(3, 3);
  fill(&matrix1, 3, 3);
  matrix2.SumMatrix(matrix1);
  ASSERT_EQ(true, matrix1.EqMatrix(matrix2));
}

TEST(s21_sum_matrix_test, Valid_Sum_2) {
  S21Matrix matrix1(2, 2), matrix2(2, 2), matrix3(2, 2);
  fill(&matrix1, 2, 2);
  fill(&matrix2, 3, 3);
  fill(&matrix3, 5, 5);
  matrix2.SumMatrix(matrix1);
  ASSERT_EQ(true, matrix2.EqMatrix(matrix3));
}

TEST(s21_sum_matrix_test, Fail_Sum_1) {
  S21Matrix matrix1(3, 2), matrix2(3, 3);
  ASSERT_THROW(matrix2.SumMatrix(matrix1), std::length_error);
}

TEST(s21_sum_matrix_test, Fail_Sum_2) {
  S21Matrix matrix1(2, 3), matrix2(3, 3);
  ASSERT_THROW(matrix2.SumMatrix(matrix1), std::length_error);
}

TEST(s21_sum_matrix_test, Sum_Operator) {
  S21Matrix matrix1(3, 3), matrix2(3, 3);
  fill(&matrix1, 3, 3);
  matrix2 = matrix2 + matrix1;
  ASSERT_EQ(true, matrix1.EqMatrix(matrix2));
}

TEST(s21_sum_matrix_test, Sum_Assignment_Operator) {
  S21Matrix matrix1(3, 3), matrix2(3, 3);
  fill(&matrix1, 3, 3);
  matrix2 += matrix1;
  ASSERT_EQ(true, matrix1.EqMatrix(matrix2));
}