#include "../../s21_decimal.h"

int s21_round_off_float(double floating_num) {
  int result;
  double integral_part, fractional_part;
  fractional_part = modf(floating_num, &integral_part);

  if (fractional_part > 0.5) integral_part += 1;
  result = (int)integral_part;

  return result;
}