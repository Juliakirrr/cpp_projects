#include "s21_matrix_tests.h"

TEST(s21_mul_number_test, Valid_Mul_1) {
  S21Matrix matrix1(2, 2), matrix2(2, 2);
  fill(&matrix1, 2, 2);
  fill(&matrix2, 4, 4);
  matrix1.MulNumber(2);
  ASSERT_EQ(true, matrix1.EqMatrix(matrix2));
}

TEST(s21_mul_number_test, Valid_Mul_2) {
  S21Matrix matrix1(3, 2), matrix2(3, 2);
  fill(&matrix1, 2, 2);
  matrix1.MulNumber(0);
  ASSERT_EQ(true, matrix1.EqMatrix(matrix2));
}

TEST(s21_mul_number_test, Mul_Operator) {
  S21Matrix matrix1(2, 2), matrix2(2, 2);
  fill(&matrix1, 2, 2);
  fill(&matrix2, 4, 4);
  matrix1 = matrix1 * 2;
  ASSERT_EQ(true, matrix1.EqMatrix(matrix2));
}

TEST(s21_mul_number_test, Mul_Assignment_Operator) {
  S21Matrix matrix1(2, 2), matrix2(2, 2);
  fill(&matrix1, 2, 2);
  fill(&matrix2, 4, 4);
  matrix1 *= 2;
  ASSERT_EQ(true, matrix1.EqMatrix(matrix2));
}