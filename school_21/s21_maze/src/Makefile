CC = gcc
CFLAGS =  -Werror -Wextra -Werror -g -std=c11
EXECUTABLE = Maze
GCOVFLAGS = -fprofile-arcs -ftest-coverage 
DIR_GAME = Maze


all: clean $(EXECUTABLE) 

$(EXECUTABLE):
	mkdir -p install_dir
	$(CC) $(CFLAGS) Maze_logic.c Maze_view.c help_functions.c main.c -lncurses -o ./install_dir/$@

$(EXECUTABLE).a:
	$(CC) $(CFLAGS) -c Maze_logic.c Maze_view.c help_functions.c
	ar rcs $@ Maze_logic.o Maze_view.o help_functions.o
	ranlib $@ 

install: $(EXECUTABLE)
	
uninstall:
	rm -rf ./install_dir/Maze
	rm -rf ./install_dir

clean:
	-rm -rf ./install_dir/Maze
	-rm -rf ./install_dir
	-rm -rf test
	-rm -rf *.o && rm -rf *.gcno
	-rm -rf *.a && rm -rf *.gcda
	-rm -rf *.info && rm -rf *.gcov
	-rm -rf ./gcov_report
	-rm -rf ./report/
	-rm -rf report.out

test: clean $(EXECUTABLE).a
	$(CC) $(CFLAGS) test.c -L. $(EXECUTABLE).a -lcheck -lncurses -o test

gcov_report: clean $(EXECUTABLE).a
	$(CC) $(GCOVFLAGS) -lncurses test.c  Maze_view.c help_functions.c Maze_logic.c -o report.out -lm -lcheck -lncurses
	./report.out
	gcov -f test.c
	lcov -t "gcov_report" -o Coverage_Report.info -c -d . --no-external
	genhtml -o ./report Coverage_Report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov_report
	xdg-open ./report/index-sort-f.html
