#include "tests.h"

int main(void) {
  int fail = 0;
  Suite *s[] = {s21_test_spin(),
                // s21_test_eq_matrix(),
                // s21_test_sum_matrix(),
                // s21_test_sub_matrix(),
                // s21_test_mult_number(),
                // s21_test_mult_matrix(),
                // s21_test_transpose(),
                // s21_test_calc_complements(),
                // s21_test_determinant(),
                // s21_test_inverse_matrix(),
                NULL};
  for (int i = 0; s[i] != NULL; i++) {
    SRunner *runner = srunner_create(s[i]);
    srunner_run_all(runner, CK_NORMAL);
    fail += srunner_ntests_failed(runner);
    srunner_free(runner);
  }
  printf("FAIL: %d\n", fail);
  return 0;
}