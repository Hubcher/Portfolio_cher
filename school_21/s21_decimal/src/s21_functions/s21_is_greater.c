#include "../s21_decimal.h"

int s21_is_greater(s21_decimal number1, s21_decimal number2) {
  int result = 0, flag = 0;
  int sign_of_number_1 = s21_get_sign(number1.bits[3]);
  int sign_of_number_2 = s21_get_sign(number2.bits[3]);

  decimal_overflow num_1 = {{
      number1.bits[0],
      number1.bits[1],
      number1.bits[2],
      0,
      0,
      0,
  }};
  decimal_overflow num_2 = {{
      number2.bits[0],
      number2.bits[1],
      number2.bits[2],
      0,
      0,
      0,
  }};

  s21_compare_and_set_exp(&num_1, &num_2, number1.bits[3], number2.bits[3]);
  if (sign_of_number_1 == sign_of_number_2) {
    for (int j = 5; j >= 0 && !result; j--) {
      unsigned int value1 = num_1.bits[j];
      unsigned int value2 = num_2.bits[j];
      if (!flag) {
        if (value1 > value2 && !sign_of_number_1)
          result = 1;
        else if (value1 < value2)
          flag++;
        if (value1 < value2 && sign_of_number_1)
          result = 1;
        else if (value1 > value2)
          flag++;
      }
    }
  } else if ((sign_of_number_1 < sign_of_number_2) &&
             !(s21_check_zero(number1) && s21_check_zero(number2))) {
    result = 1;
  }
  return result;
}