#include "../../s21_decimal.h"

int s21_overflow_binary_addition(decimal_overflow value_1,
                                 decimal_overflow value_2,
                                 decimal_overflow *result) {
  short error = 0, in_my_mind = 0;
  int bit1, bit2;
  s21_initialize_overflow(result);
  for (int j = 0; j < 6; j++) {
    for (int i = 0; i < 32; i++) {
      bit1 = s21_check_bit_state(value_1.bits[j], i);
      bit2 = s21_check_bit_state(value_2.bits[j], i);
      if (bit1 && bit2) {
        if (in_my_mind) {
          result->bits[j] = s21_set_bit(result->bits[j], i);
        } else {
          in_my_mind = 1;
        }
      } else if (bit1 ^ bit2) {
        if (!in_my_mind) {
          result->bits[j] = s21_set_bit(result->bits[j], i);
        }
      } else if (in_my_mind) {
        result->bits[j] = s21_set_bit(result->bits[j], i);
        in_my_mind = 0;
      }
    }
    if (in_my_mind && j == 5) error = 1;
  }
  return error;
}
