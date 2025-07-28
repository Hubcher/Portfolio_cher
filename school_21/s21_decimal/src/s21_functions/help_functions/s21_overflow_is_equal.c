#include "../../s21_decimal.h"

int s21_overflow_is_equal(decimal_overflow number1, decimal_overflow number2) {
  int result = 1;
  for (int i = 5; i >= 0; i--) {
    unsigned int value1 = number1.bits[i];
    unsigned int value2 = number2.bits[i];
    if (value1 != value2) {
      result = 0;
    }
  }
  return result;
}