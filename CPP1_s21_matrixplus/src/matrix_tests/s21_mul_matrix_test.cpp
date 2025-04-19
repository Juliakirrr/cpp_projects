#include "s21_matrix_tests.h"

TEST(s21_mul_matrix_test, Valid_Mul_1) {
  S21Matrix matrix1(2, 2), matrix2(2, 2), matrix3(2, 2);
  fill(&matrix1, 2, 2);
  fill(&matrix2, 3, 3);
  matrix3.getMatrix()[0][0] = 42;
  matrix3.getMatrix()[0][1] = 60;
  matrix3.getMatrix()[1][0] = 90;
  matrix3.getMatrix()[1][1] = 132;
  matrix1.MulMatrix(matrix2);
  ASSERT_EQ(true, matrix1.EqMatrix(matrix3));
}

TEST(s21_mul_matrix_test, Valid_Mul_2) {
  S21Matrix matrix1(2, 3), matrix2(3, 2), matrix3(2, 2);
  fill(&matrix1, 2, 2);
  fill(&matrix2, 3, 3);
  matrix3.getMatrix()[0][0] = 132;
  matrix3.getMatrix()[0][1] = 168;
  matrix3.getMatrix()[1][0] = 294;
  matrix3.getMatrix()[1][1] = 384;
  matrix1.MulMatrix(matrix2);
  ASSERT_EQ(true, matrix1.EqMatrix(matrix3));
}

TEST(s21_mul_matrix_test, Valid_Mul_3) {
  S21Matrix matrix1(2, 3), matrix2(3, 3), matrix3(2, 3);
  fill(&matrix1, 2, 2);
  fill(&matrix2, 3, 3);
  matrix3.getMatrix()[0][0] = 180;
  matrix3.getMatrix()[0][1] = 216;
  matrix3.getMatrix()[0][2] = 252;
  matrix3.getMatrix()[1][0] = 396;
  matrix3.getMatrix()[1][1] = 486;
  matrix3.getMatrix()[1][2] = 576;
  matrix1.MulMatrix(matrix2);
  ASSERT_EQ(true, matrix1.EqMatrix(matrix3));
}

TEST(s21_mul_matrix_test, Fail_Mul_1) {
  S21Matrix matrix1(2, 2), matrix2(3, 3);
  ASSERT_THROW(matrix1.MulMatrix(matrix2), std::length_error);
}

TEST(s21_mul_matrix_test, Mul_Operator) {
  S21Matrix matrix1(2, 2), matrix2(2, 2), matrix3(2, 2);
  fill(&matrix1, 2, 2);
  fill(&matrix2, 3, 3);
  matrix3.getMatrix()[0][0] = 42;
  matrix3.getMatrix()[0][1] = 60;
  matrix3.getMatrix()[1][0] = 90;
  matrix3.getMatrix()[1][1] = 132;
  matrix1 = matrix1 * matrix2;
  ASSERT_EQ(true, matrix1.EqMatrix(matrix3));
}

TEST(s21_mul_matrix_test, Mul_Assignment_Operator) {
  S21Matrix matrix1(2, 2), matrix2(2, 2), matrix3(2, 2);
  fill(&matrix1, 2, 2);
  fill(&matrix2, 3, 3);
  matrix3.getMatrix()[0][0] = 42;
  matrix3.getMatrix()[0][1] = 60;
  matrix3.getMatrix()[1][0] = 90;
  matrix3.getMatrix()[1][1] = 132;
  matrix1 *= matrix2;
  ASSERT_EQ(true, matrix1.EqMatrix(matrix3));
}