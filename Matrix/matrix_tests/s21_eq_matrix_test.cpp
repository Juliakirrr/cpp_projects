#include "s21_matrix_tests.h"

TEST(s21_eq_matrix_test, Valid_Eq_1) {
  S21Matrix matrix1(3, 3), matrix2(3, 3);
  fill(&matrix1, 3, 3);
  fill(&matrix2, 3, 3);
  ASSERT_EQ(true, matrix1.EqMatrix(matrix2));
}

TEST(s21_eq_matrix_test, Valid_Eq_Prec) {
  S21Matrix matrix1(3, 3), matrix2(3, 3);
  matrix1(1, 1) = 5.00000005;
  matrix2(1, 1) = 5.00000006;
  ASSERT_EQ(true, matrix1.EqMatrix(matrix2));
}

TEST(s21_eq_matrix_test, Null_Eq_1) {
  S21Matrix matrix1, matrix2(2, 2);
  ASSERT_THROW(matrix1.EqMatrix(matrix2), std::length_error);
}

TEST(s21_eq_matrix_test, Null_Eq_2) {
  S21Matrix matrix1(2, 2), matrix2;
  ASSERT_THROW(matrix1.EqMatrix(matrix2), std::length_error);
}

TEST(s21_eq_matrix_test, Fail_Eq_1) {
  S21Matrix matrix1(2, 3), matrix2(3, 3);
  ASSERT_EQ(false, matrix1.EqMatrix(matrix2));
}

TEST(s21_eq_matrix_test, Fail_Eq_2) {
  S21Matrix matrix1(3, 2), matrix2(3, 3);
  ASSERT_EQ(false, matrix1.EqMatrix(matrix2));
}

TEST(s21_eq_matrix_test, Fail_Eq_3) {
  S21Matrix matrix1(3, 3), matrix2(3, 3);
  fill(&matrix1, 3, 3);
  fill(&matrix2, 3, 3);
  matrix2.getMatrix()[1][1] = 5;
  ASSERT_EQ(false, matrix1.EqMatrix(matrix2));
}

TEST(s21_eq_matrix_test, Fail_Eq_Prec) {
  S21Matrix matrix1(3, 3), matrix2(3, 3);
  matrix1(1, 1) = 5.0000005;
  matrix2(1, 1) = 5.0000006;
  ASSERT_EQ(false, matrix1.EqMatrix(matrix2));
}

TEST(s21_eq_matrix_test, Valid_Assignment_Operator) {
  S21Matrix matrix1(3, 3), matrix2(3, 3), matrix3(3, 3);
  fill(&matrix1, 3, 3);
  fill(&matrix2, 3, 3);
  matrix3 = matrix2;
  ASSERT_EQ(true, matrix1.EqMatrix(matrix3));
}