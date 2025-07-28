#include "../../s21_decimal.h"

decimal_overflow multiply_large_numbers(decimal_overflow value_1,
                                        decimal_overflow value_2) {
  decimal_overflow tmp = {{0, 0, 0, 0, 0, 0}};
  decimal_overflow res = {{0, 0, 0, 0, 0, 0}};
  for (int i = 0; i < 192; i++) {
    if (s21_check_bit_state(value_1.bits[i / 32], i % 32)) {
      s21_initialize_overflow(&tmp);
      s21_copy_overflow(&tmp, res);
      s21_overflow_binary_addition(tmp, overflow_s21_left_n_times(value_2, i),
                                   &res);
    }
  }
  return res;
}