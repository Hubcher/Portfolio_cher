#include "../../s21_decimal.h"

int s21_get_sign(int num) { return s21_check_bit_state(num, 31); }