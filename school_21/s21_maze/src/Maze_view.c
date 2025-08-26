#include "Maze.h"

void printField(int rows, int cols, int scale) {
  clear();
  int y = 0;
  int x = 0;
  cols *= scale;
  rows *= scale;
  mvaddch(y, x, ACS_ULCORNER);
  for (x = 1; x < cols; x++) {
    mvaddch(y, x, ACS_HLINE);
  }
  mvaddch(y, x, ACS_URCORNER);

  for (y = 1; y < rows; y++) {
    mvaddch(y, cols, ACS_VLINE);
  }
  mvaddch(y, cols, ACS_LRCORNER);

  for (x = cols - 1; x >= 0; x--) {
    mvaddch(y, x, ACS_HLINE);
  }
  mvaddch(y, 0, ACS_LLCORNER);

  for (y = rows - 1; y > 0; y--) {
    mvaddch(y, 0, ACS_VLINE);
  }
}

void drawRightWall(int y, int x, int scale, int rows) {
  if (y == 0) mvaddch(y * scale, x * scale, ACS_TTEE);
  for (int i = 0; i < scale; i++) {
    if (i + 1 != scale || y + 1 != rows)
      mvaddch(y * scale + i + 1, x * scale, ACS_VLINE);
    else
      mvaddch(y * scale + i + 1, x * scale, ACS_BTEE);
  }
}

void drawUnderWall(int y, int x, int scale, int cols, int rows, int** Vline,
                   int** Gline) {
  if (x == 0) {
    mvaddch((y + 1) * scale, x * scale, ACS_LTEE);
  } else if (Vline[y][x - 1] && Vline[y + 1][x - 1]) {
    if (Gline[y][x - 1])
      mvaddch((y + 1) * scale, x * scale, ACS_PLUS);
    else
      mvaddch((y + 1) * scale, x * scale, ACS_LTEE);
  } else if (Vline[y + 1][x - 1]) {
    if (Gline[y][x - 1])
      mvaddch((y + 1) * scale, x * scale, ACS_TTEE);
    else
      mvaddch((y + 1) * scale, x * scale, ACS_ULCORNER);
  } else if (Vline[y][x - 1])
    if (Gline[y][x - 1])
      mvaddch((y + 1) * scale, x * scale, ACS_BTEE);
    else
      mvaddch((y + 1) * scale, x * scale, ACS_LLCORNER);

  for (int i = 0; i < scale; i++) {
    if (i + 1 != scale || !(Vline[y][x] || Vline[y + 1][x])) {
      mvaddch((y + 1) * scale, x * scale + i + 1, ACS_HLINE);
    } else if (Vline[y][x] && Vline[y + 1][x])
      mvaddch((y + 1) * scale, x * scale + i + 1, ACS_RTEE);
    else if (Vline[y][x])
      mvaddch((y + 1) * scale, x * scale + i + 1, ACS_LRCORNER);
    else if (Vline[y + 1][x])
      mvaddch((y + 1) * scale, x * scale + i + 1, ACS_URCORNER);
    else
      mvaddch((y + 1) * scale, x * scale + i + 1, ACS_RTEE);
  }
}

void drawMaze(int rows, int cols, int scale, int** Vline, int** Gline) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (Vline[i][j] == 1 && j + 1 != cols)
        drawRightWall(i, j + 1, scale, rows);
    }
  }
  for (int i = 0; i < rows - 1; i++) {
    for (int j = 0; j < cols; j++) {
      if (Gline[i][j] == 1)
        drawUnderWall(i, j, scale, cols, rows, Vline, Gline);
    }
  }
}