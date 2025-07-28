#include "../../s21_decimal.h"

int s21_add_value(s21_decimal num1, s21_decimal num2, s21_decimal *result) {
  int carry = 0;
  int sum;
  s21_initialize_decimal(result);
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < 32; i++) {
      sum = s21_check_bit_state(num1.bits[j], i) +
            s21_check_bit_state(num2.bits[j], i) + carry;
      if (sum >= 2) {
        carry = 1;
      } else {
        carry = 0;
      }
      if (sum % 2 == 1) {
        result->bits[j] = s21_set_bit(result->bits[j], i);
      }
    }
    if (carry && j == 2) return 1;
  }
  return carry;
}