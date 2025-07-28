#include "../s21_tests.h"

int run_suite(Suite *suite);

int main(void) {
  int total_failed_count = 0;  // Общее количество неудачных тестов

  // Создание и запуск тестовых наборов
  total_failed_count += run_suite(suite_add());
  total_failed_count += run_suite(suite_sub());
  total_failed_count += run_suite(suite_div());
  total_failed_count += run_suite(suite_mul());
  total_failed_count += run_suite(suite_is_equal());
  total_failed_count += run_suite(suite_converter());
  total_failed_count += run_suite(suite_floor());
  total_failed_count += run_suite(suite_round());
  total_failed_count += run_suite(suite_negate());

  // Возврат статуса завершения программы в зависимости от количества
  // неудачных тестов
  return (total_failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

int run_suite(Suite *suite) {
  int failed_count;

  // Создание исполнителя тестов для данного тестового набора
  SRunner *suite_runner = srunner_create(suite);

  // Запуск всех тестов в данном тестовом наборе
  srunner_run_all(suite_runner, CK_NORMAL);

  // Получение количества неудачных тестов
  failed_count = srunner_ntests_failed(suite_runner);

  // Освобождение ресурсов исполнителя тестов
  srunner_free(suite_runner);

  // Возвращаем количество неудачных тестов в данном тестовом наборе
  return failed_count;
}
