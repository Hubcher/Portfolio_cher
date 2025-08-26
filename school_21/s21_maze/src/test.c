#include <check.h>
#include <stdlib.h>
#include <time.h>

#include "Maze.h"

// Тесты для функции allocate2DArray
START_TEST(test_allocate2DArray) {
  int rows = 5, cols = 5;
  int** array = allocate2DArray(rows, cols);
  ck_assert_ptr_nonnull(array);
  for (int i = 0; i < rows; i++) {
    ck_assert_ptr_nonnull(array[i]);
  }
  free2DArray(array, rows);
}
END_TEST

// Тесты для генерации лабиринта
START_TEST(test_generateMaze) {
  int rows = 4, cols = 4;
  int** Vline = allocate2DArray(rows, cols);
  int** Gline = allocate2DArray(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      Vline[i][j] = 0;
      Gline[i][j] = 0;
    }
  }

  generateMaze(rows, cols, Vline, Gline);

  int wall_count = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      wall_count += Vline[i][j] + Gline[i][j];
    }
  }
  ck_assert_int_ge(wall_count, cols - 1);  // Проверяем, что есть стены
  free2DArray(Vline, rows);
  free2DArray(Gline, rows);
}
END_TEST

START_TEST(test_view) { printField(5, 5, 3); }
END_TEST

// Тесты для загрузки лабиринта из файла
START_TEST(test_loadMap_file) {
  FILE* file = fopen("test_map.txt", "w");
  fprintf(file, "3 3\n0 1 0\n1 0 1\n0 0 1\n1 0 0\n0 1 0\n");
  fclose(file);

  file = fopen("test_map.txt", "r");
  ck_assert_ptr_nonnull(file);

  int rows, cols;
  ck_assert_int_eq(readRowsCols(file, &rows, &cols), 0);
  ck_assert_int_eq(rows, 3);
  ck_assert_int_eq(cols, 3);

  int** Vline = allocate2DArray(rows, cols);
  int** Gline = allocate2DArray(rows, cols);

  readingVerticalLine(file, rows, cols, Vline);
  readingGorizontalLine(file, rows, cols, Gline);

  ck_assert_int_eq(Vline[0][1], 1);
  ck_assert_int_eq(Gline[1][0], 0);

  fclose(file);
  free2DArray(Vline, rows);
  free2DArray(Gline, rows);
  remove("test_map.txt");
}
END_TEST

// Тесты для проверки перемещения в лабиринте
START_TEST(test_canMove) {
  int rows = 3, cols = 3;
  int** Vline = allocate2DArray(rows, cols);
  int** Gline = allocate2DArray(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      Vline[i][j] = 0;
      Gline[i][j] = 0;
    }
  }

  ck_assert(canMove(0, 0, 1, 0, rows, cols, Vline, Gline));  // Вправо
  ck_assert(canMove(0, 0, 0, 1, rows, cols, Vline, Gline));  // Вниз

  Vline[0][0] = 1;  // Стена справа
  ck_assert(!canMove(0, 0, 1, 0, rows, cols, Vline, Gline));  // Вправо нельзя

  free2DArray(Vline, rows);
  free2DArray(Gline, rows);
}
END_TEST

START_TEST(test_WALL) {
  drawRightWall(0, 0, 3, 4);
  int** Vline = allocate2DArray(4, 4);
  int** Gline = allocate2DArray(4, 4);
  drawUnderWall(1, 1, 3, 4, 4, Vline, Gline);
  drawUnderWall(1, 0, 3, 4, 4, Vline, Gline);
  Vline[1][0] = 1;
  Vline[2][0] = 1;
  Gline[1][0] = 1;
  drawUnderWall(1, 1, 3, 4, 4, Vline, Gline);
  Gline[1][0] = 0;
  drawUnderWall(1, 1, 3, 4, 4, Vline, Gline);

  drawMaze(4, 4, 3, Vline, Gline);
}
END_TEST

START_TEST(test_map) { loadMap(); }
END_TEST

START_TEST(test_map_2) { createMap(); }
END_TEST

START_TEST(test_file) {
  FILE* file = fopen("map2.txt", "r");
  openFile(file);
}
END_TEST

START_TEST(test_rowscols) {
  FILE* file = fopen("map.txt", "r");
  int rows = 51;
  int cols = 2;
  readRowsCols(file, &rows, &cols);
}
END_TEST

Suite* suite_create_maze(void) {
  Suite* suite = suite_create("s21_maze");
  // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
  TCase* tcase_core = tcase_create("maze");

  // Добавление теста в группу тестов.
  tcase_add_test(tcase_core, test_allocate2DArray);
  tcase_add_test(tcase_core, test_generateMaze);
  tcase_add_test(tcase_core, test_view);
  tcase_add_test(tcase_core, test_loadMap_file);
  tcase_add_test(tcase_core, test_canMove);
  tcase_add_test(tcase_core, test_WALL);
  tcase_add_test(tcase_core, test_map);
  tcase_add_test(tcase_core, test_map_2);
  tcase_add_test(tcase_core, test_file);
  tcase_add_test(tcase_core, test_rowscols);

  // Добавление теста в тестовый набор.
  suite_add_tcase(suite, tcase_core);

  return suite;
}

int main(void) {
  int failed_count;
  Suite* suite = suite_create_maze();
  SRunner* suite_runner = srunner_create(suite);

  srunner_run_all(suite_runner, CK_NORMAL);
  failed_count =
      srunner_ntests_failed(suite_runner);  // запускаем все тестовые случаи
  srunner_free(suite_runner);
  return (failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
