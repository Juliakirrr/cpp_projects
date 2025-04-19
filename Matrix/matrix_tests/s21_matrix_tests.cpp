#include "s21_matrix_tests.h"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

void fill(S21Matrix *matrix, double value, double append) {
  for (int i = 0; i < matrix->getRows(); i++) {
    for (int j = 0; j < matrix->getCols(); j++) {
      matrix->getMatrix()[i][j] = value;
      value += append;
    }
  }
}