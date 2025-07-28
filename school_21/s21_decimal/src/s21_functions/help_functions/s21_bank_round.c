#include "../../s21_decimal.h"

void s21_bank_round(decimal_overflow value, decimal_overflow *result) {
  if (result) {
    s21_initialize_overflow(result);
    decimal_overflow mod1, mod2;
    s21_initialize_overflow(&mod1);
    s21_initialize_overflow(&mod2);
    decimal_overflow one = {{1, 0, 0, 0, 0, 0}};
    s21_mod10(value, &mod1);
    s21_divide_by_10_overflow(&value);
    if (mod1.bits[0] > 5) {
      s21_overflow_binary_addition(value, one, &value);
    } else if (mod1.bits[0] == 5) {
      s21_mod10(value, &mod2);
      if (mod2.bits[0] % 2 != 0)
        s21_overflow_binary_addition(value, one, &value);
    }
  }
  *result = value;
}
