#ifndef S21_TESTS_H
#define S21_TESTS_H

#include <check.h>
#include <stdio.h>

#include "s21_decimal.h"

Suite *suite_add(void);
Suite *suite_sub(void);
Suite *suite_mul(void);
Suite *suite_div(void);

Suite *suite_is_equal(void);

Suite *suite_converter(void);

Suite *suite_floor(void);
Suite *suite_round(void);
Suite *suite_truncate(void);
Suite *suite_negate(void);

#endif