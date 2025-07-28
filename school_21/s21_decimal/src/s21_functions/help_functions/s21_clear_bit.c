#include "../../s21_decimal.h"

int s21_clear_bit(int num, int idx) { return (num & ~(1 << idx)); }