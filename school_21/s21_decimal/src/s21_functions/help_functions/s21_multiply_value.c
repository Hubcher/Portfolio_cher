#include "../../s21_decimal.h"

int s21_multiply_value(s21_decimal value_1, s21_decimal value_2,
                       s21_decimal *result) {
  int status = 0;
  s21_decimal temp = {0};
  s21_decimal res = {0};
  s21_decimal val1_cp = {0};
  if (result) {
    for (int i = 0; i < 96 && !status; i++) {
      if (s21_check_bit_state(value_2.bits[i / 32], i % 32)) {
        s21_initialize_decimal(&temp);
        s21_assign_value(&val1_cp, value_1);
        s21_assign_value(&temp, res);
        status =
            s21_left_n_times(&val1_cp, i) + s21_add_value(temp, val1_cp, &res);
      }
    }
    if (status == 0) s21_assign_value(result, res);
  }
  return status;
}