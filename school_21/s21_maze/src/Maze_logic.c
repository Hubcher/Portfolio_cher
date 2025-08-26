#include "Maze.h"

int loadMap() {
  FILE* file = fopen("map.txt", "r");
  if (openFile(file)) return 1;

  int rows = 0, cols = 0;
  if (readRowsCols(file, &rows, &cols)) return 1;

  int scale = 3;
  printField(rows, cols, scale);

  int** Vline = allocate2DArray(rows, cols);
  int** Gline = allocate2DArray(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      Vline[i][j] = 0;
      Gline[i][j] = 0;
    }
  }

  readingVerticalLine(file, rows, cols, Vline);
  readingGorizontalLine(file, rows, cols, Gline);

  drawMaze(rows, cols, scale, Vline, Gline);
  solveMaze(rows, cols, Vline, Gline);

  fclose(file);
  getch();
  return 0;
}

int createMap() {
  int scale = 3;
  int rows = 2, cols = 2;
  echo();
  scanw("%d %d", &rows, &cols);
  noecho();
  printField(rows, cols, scale);

  int** Vline = allocate2DArray(rows, cols);
  int** Gline = allocate2DArray(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      Vline[i][j] = 0;
      Gline[i][j] = 0;
    }
  }
  generateMaze(rows, cols, Vline, Gline);

  drawMaze(rows, cols, scale, Vline, Gline);
  solveMaze(rows, cols, Vline, Gline);

  free2DArray(Vline, rows);
  free2DArray(Gline, rows);

  getch();
  return 0;
}

void generateMaze(int rows, int cols, int** Vline, int** Gline) {
  int* sets = (int*)malloc(cols * sizeof(int));  // массив для множеств
  int counter = 1;

  // Инициализация множеств
  for (int i = 0; i < cols; i++) {
    sets[i] = 0;
  }

  // Добавление уникальных значений в множества
  void Add_unique_values_to_set() {
    for (int i = 0; i < cols; ++i) {
      if (sets[i] == 0) {
        sets[i] = counter++;
      }
    }
  }

  // Объединение множеств
  void Merge_sets(int pos, int set) {
    int old_set = sets[pos + 1];
    for (int i = 0; i < cols; ++i) {
      if (sets[i] == old_set) {
        sets[i] = set;
      }
    }
  }

  // Подсчет элементов в множестве
  int Count_set_members(int set) {
    int res = 0;
    for (int i = 0; i < cols; ++i) {
      if (sets[i] == set) {
        ++res;
      }
    }
    return res;
  }

  // Подсчет горизонтальных стен в множестве
  int Count_walls(int set, int row) {
    int res = 0;
    for (int i = 0; i < cols; ++i) {
      if (sets[i] == set && Gline[row][i]) {
        ++res;
      }
    }
    return res;
  }

  void Add_vertical_walls(int row) {
    for (int i = 0; i < cols - 1; ++i) {
      if (sets[i] != sets[i + 1] && rand() % 2 == 0) {
        Vline[row][i] = 1;
      } else {
        Merge_sets(i, sets[i]);
      }
    }
    Vline[row][cols - 1] = 1;
  }

  void Add_horizontal_walls(int row) {
    for (int i = 0; i < cols; ++i) {
      if (Count_set_members(sets[i]) > 1 && rand() % 2 == 0) {
        Gline[row][i] = 1;
      }
    }
  }

  // Проверка на изолированные множества
  void Check_for_set_isolation(int row) {
    for (int i = 0; i < cols; ++i) {
      if (Count_set_members(sets[i]) == Count_walls(sets[i], row)) {
        Gline[row][i] = 0;
      }
    }
  }

  // Подготовка множеств для следующей строки
  void Prepare_sets_for_new_Line(int row) {
    for (int i = 0; i < cols; ++i) {
      if (Gline[row][i]) {
        sets[i] = 0;
      }
    }
  }

  // Обработка последней строки
  void Check_last_line() {
    for (int i = 0; i < cols - 1; ++i) {
      if (sets[i] != sets[i + 1]) {
        Vline[rows - 1][i] = 0;
        Merge_sets(i, sets[i]);
      }
      Gline[rows - 1][i] = 1;
    }
    Vline[rows - 1][cols - 1] = 1;
    Gline[rows - 1][cols - 1] = 1;
  }

  // Основной цикл генерации лабиринта
  for (int i = 0; i < rows - 1; ++i) {
    Add_unique_values_to_set();
    Add_vertical_walls(i);
    Add_horizontal_walls(i);
    Check_for_set_isolation(i);
    Prepare_sets_for_new_Line(i);
  }

  // Обработка последней строки
  Add_unique_values_to_set();
  Add_vertical_walls(rows - 1);
  Check_last_line();

  free(sets);
}

bool canMove(int x, int y, int nextX, int nextY, int rows, int cols,
             int** Vline, int** Gline) {
  if (nextX < 0 || nextY < 0 || nextX >= cols || nextY >= rows) {
    return false;
  }

  if (nextX == x + 1 && Vline[y][x] == 1) return false;
  if (nextX == x - 1 && Vline[y][x - 1] == 1) return false;
  if (nextY == y + 1 && Gline[y][x] == 1) return false;
  if (nextY == y - 1 && Gline[y - 1][x] == 1) return false;

  return true;
}

bool findPath(int x, int y, int rows, int cols, int** Vline, int** Gline,
              int path[][cols], int destX, int destY) {
  if (x == destX && y == destY) {
    path[y][x] = 1;
    return true;
  }

  path[y][x] = 1;

  int directions[4][2] = {
      {1, 0},   // Вправо
      {0, 1},   // Вниз
      {-1, 0},  // Влево
      {0, -1}   // Вверх
  };

  for (int i = 0; i < 4; i++) {
    int nextX = x + directions[i][0];
    int nextY = y + directions[i][1];

    if (canMove(x, y, nextX, nextY, rows, cols, Vline, Gline) &&
        path[nextY][nextX] == 0) {
      if (findPath(nextX, nextY, rows, cols, Vline, Gline, path, destX,
                   destY)) {
        return true;
      }
    }
  }

  path[y][x] = 0;
  return false;
}

void solveMaze(int rows, int cols, int** Vline, int** Gline) {
  int path[rows][cols];

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      path[i][j] = 0;
    }
  }
  int startX, startY;
  int destX, destY;

  echo();
  move(rows * 3 + 1, 0);
  printw("Write the starting point in the format: X Y\n");
  scanw("%d %d", &startX, &startY);
  printw("Write the end point in the format:X Y\n");
  scanw("%d %d", &destX, &destY);
  noecho();

  if (findPath(startX, startY, rows, cols, Vline, Gline, path, destX, destY)) {
    int check = 0;
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (path[i][j] == 1) {
          start_color();
          init_pair(1, COLOR_WHITE, COLOR_GREEN);
          attron(COLOR_PAIR(1)); /* use the above combination */
          if (i == startY && j == startX)
            mvaddch(i * 3 + 1, j * 3 + 1, 'O');
          else if (i == destY && j == destX)
            mvaddch(i * 3 + 1, j * 3 + 1, 'X');
          else
            mvaddch(i * 3 + 1, j * 3 + 1, ' ');
          attroff(COLOR_PAIR(1)); /* turn color off */
        }
      }
    }
  } else {
    clear();
    printw("Path not found\n");
  }
}
