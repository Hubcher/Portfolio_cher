#include "Maze.h"

int main() {
  setlocale(LC_ALL, "");
  initscr();
  refresh();
  curs_set(0);
  keypad(stdscr, 1);
  noecho();
  printw("Select an option: \n1. Download the Maze\n2. Generate the Maze");
  int choose = getch();
  if (choose == '1') {
    loadMap();
  } else if (choose == '2') {
    clear();
    printw("Enter the size of the maze in the format:X Y\n");
    createMap();
  }
  endwin();
  return 0;
}
