#include "../../s21_decimal.h"

int s21_first_large_number_greater(decimal_overflow number1,
                                   decimal_overflow number2) {
  int result = 0, flag = 0;
  for (int j = 5; j >= 0 && !result; j--) {
    unsigned int value1 = number1.bits[j];
    unsigned int value2 = number2.bits[j];
    if (!flag) {
      if (value1 > value2)
        result = 1;
      else if (value1 < value2)
        flag++;
    }
  }
  return result;
}