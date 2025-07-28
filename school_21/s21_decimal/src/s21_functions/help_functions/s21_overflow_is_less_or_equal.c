#include "../../s21_decimal.h"

int s21_overflow_is_less_or_equal(decimal_overflow number1,
                                  decimal_overflow number2) {
  return !s21_first_large_number_greater(number1, number2);
}