#include "../../s21_decimal.h"

void s21_normalize_to_lower_exp(decimal_overflow input_value,
                                s21_decimal *output_result) {
  while (input_value.bits[3] || input_value.bits[4] || input_value.bits[5] ||
         (s21_get_exp(output_result->bits[3]) > 28)) {
    s21_bank_round(input_value, &input_value);
    output_result->bits[3] -= 1 << 16;
  }
  output_result->bits[0] = input_value.bits[0];
  output_result->bits[1] = input_value.bits[1];
  output_result->bits[2] = input_value.bits[2];
}