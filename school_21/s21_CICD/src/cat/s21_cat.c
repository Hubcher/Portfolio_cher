#include <errno.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>

#include "catFlags.h"

typedef struct {
  bool flag_b;  // нумерует только непустые строки
  bool flag_e;  // отображает символы конца строки как $
  bool flag_n;  // нумерует все выходные строки
  bool flag_s;  // сжимает несколько смежных пустых строк
  bool tab;  // отображает табы как ^I
  bool printNonPrintable;
} Flags;

Flags Parcer_flags(int argc, char *argv[]) {
  struct option longOptions[] = {
      {"number-nonblank", 0, NULL, 'b'},
      {"number", 0, NULL, 'n'},
      {"squeeze-blank", 0, NULL, 's'},
      {NULL, 0, NULL, 0}  // для того, чтобы getopt_long знал, когда закончились
                          // опции и необходимо прекратить их обработку.
  };

  int current_flag = getopt_long(argc, argv, "+bevEnsvtT", longOptions, NULL);

  Flags flags = {false, false, false, false, false, false};
  for (; current_flag != -1;  // если опций больше нет, функция возвращает -1.
       current_flag =
           getopt_long(argc, argv, "+bevEnsvtT", longOptions, NULL)) {
    switch (current_flag) {
      break;
      case 'b':
        flags.flag_b = true;
        break;
      case 'e':
        flags.flag_e = true;
        flags.printNonPrintable = true;
        break;
      case 'v':
        flags.printNonPrintable = true;
        break;
      case 'E':
        flags.flag_e = true;
        break;
      case 'n':
        flags.flag_n = true;
        break;
      case 's':
        flags.flag_s = true;
        break;
      case 't':
        flags.printNonPrintable = true;
        flags.tab = true;
    }
  }
  return flags;
}

void CatFile(FILE *file, Flags flags, const char *table[static 256]) {
  int current_char = 0;
  int last = '\n';
  ;
  bool squeeze = false;
  int number_line = 0;
  while (fread(&current_char, 1, 1, file) > 0) {
    if (last == '\n') {
      if (flags.flag_s && current_char == '\n') {
        if (squeeze) continue;
        squeeze = true;
      } else {
        squeeze = false;
      }
      if (flags.flag_b) {
        if (current_char != '\n') printf("%6i\t", ++number_line);
      } else if (flags.flag_n) {
        printf("%6i\t", ++number_line);
      }
    }
    if (!*table[current_char])
      printf("%c", '\0');
    else
      printf("%s", table[current_char]);
    last = current_char;
  }
}

void Cat(int argc, char *argv[], Flags flags, const char *table[static 256]) {
  for (char **filename = &argv[1], **end = &argv[argc]; filename != end;
       ++filename) {
    if (**filename == '-') continue;
    FILE *file = fopen(*filename, "rb");
    if (errno) {
      fprintf(stderr, "cat: %s: No such file or directory\n", argv[optind]);
      perror(*filename);
      continue;
    }
    CatFile(file, flags, table);
    fclose(file);
  }
}

int main(int argc, char **argv) {
  Flags flags = Parcer_flags(argc, argv);

  const char *table[256];
  CatSetTable(table);

  if (flags.flag_e) CatSetEndl(table);
  if (flags.tab) CatSetTab(table);
  if (flags.printNonPrintable) CatSetNonPrintable(table);

  Cat(argc, argv, flags, table);

  return 0;
}