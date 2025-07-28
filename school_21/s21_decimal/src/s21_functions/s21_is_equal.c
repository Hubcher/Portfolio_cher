#include "../s21_decimal.h"

int s21_is_equal(s21_decimal number1, s21_decimal number2) {
  int result = 1;
  decimal_overflow num_1 = {{number1.bits[0], number1.bits[1], number1.bits[2],
                             0, 0, 0}},
                   num_2 = {{number2.bits[0], number2.bits[1], number2.bits[2],
                             0, 0, 0}};
  s21_compare_and_set_exp(&num_1, &num_2, number1.bits[3], number2.bits[3]);
  if (s21_get_sign(number1.bits[3]) == s21_get_sign(number2.bits[3])) {
    int i = 5;
    while (result && i >= 0) {
      result = (num_1.bits[i] == num_2.bits[i]);
      i--;
    }
  } else {
    result = s21_check_zero(number1) && s21_check_zero(number2);
  }
  return result;
}