#include <locale.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printField(int rows, int cols, int scale);
void readingVerticalLine(FILE* file, int rows, int cols, int** Vline);
void readingGorizontalLine(FILE* file, int rows, int cols, int** Gline);
void drawRightWall(int y, int x, int scale, int rows);
void drawUnderWall(int y, int x, int scale, int cols, int rows, int** Vline,
                   int** Gline);
int openFile(FILE* file);
int readRowsCols(FILE* file, int* rows, int* cols);
int createMap();
void drawMaze(int rows, int cols, int scale, int** Vline, int** Gline);
void generateMaze(int rows, int cols, int** Vline, int** Gline);
void solveMaze(int rows, int cols, int** Vline, int** Gline);
int** allocate2DArray(int rows, int cols);
int loadMap();
void initializeRow(int* sets, int cols);
void free2DArray(int** array, int rows);
bool canMove(int x, int y, int nextX, int nextY, int rows, int cols,
             int** Vline, int** Gline);
