#include "Maze.h"

int openFile(FILE* file) {
  if (!file) {
    clear();
    printw("Ошибка: не удалось открыть файл map.txt\n");
    getch();
    return 1;
  }
  return 0;
}

int readRowsCols(FILE* file, int* rows, int* cols) {
  fscanf(file, "%d %d", rows, cols);
  if (*rows < 1 || *cols < 1 || *rows > 50 || *cols > 50) {
    clear();
    printw("Ошибка: Некорректный размер лабиринта!");
    getch();
    fclose(file);
    return 1;
  }
  return 0;
}

int** allocate2DArray(int rows, int cols) {
  int** array = malloc(rows * sizeof(int*));
  for (int i = 0; i < rows; i++) {
    array[i] = malloc(cols * sizeof(int));
  }
  return array;
}

void free2DArray(int** array, int rows) {
  for (int i = 0; i < rows; i++) {
    free(array[i]);
  }
  free(array);
}

void readingVerticalLine(FILE* file, int rows, int cols, int** Vline) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (fscanf(file, "%d", &Vline[i][j]) != 1) {
        fprintf(stderr, "Error reading file at position (%d, %d)\n", i, j);
        return;
      }
    }
  }
}

void readingGorizontalLine(FILE* file, int rows, int cols, int** Gline) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (fscanf(file, "%d", &Gline[i][j]) != 1) {
        fprintf(stderr, "Error reading file at position (%d, %d)\n", i, j);
        return;
      }
    }
  }
}
