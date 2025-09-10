CC = gcc
CFLAGS =  -Werror -Wextra -Werror -g -std=c11
EXECUTABLE = tetris
GCOVFLAGS = -fprofile-arcs -ftest-coverage
DIR_INTERFACE = ./gui/cli
DIR_GAME = ./brick_game/tetris
DOCS = ./docs/documentation.tex  

all: clean $(EXECUTABLE) test dist dvi gcov_report 

$(EXECUTABLE):
	mkdir -p install_dir
	$(CC) $(CFLAGS) $(DIR_GAME)/game_logic.c $(DIR_INTERFACE)/interface.c $(DIR_GAME)/main.c -lncurses -o ./install_dir/$@

$(EXECUTABLE).a:
	$(CC) $(CFLAGS) -c $(DIR_GAME)/game_logic.c $(DIR_INTERFACE)/interface.c
	ar rcs $@ game_logic.o interface.o
	ranlib $@

install: $(EXECUTABLE)
	

uninstall:
	rm -rf ./install_dir/tetris
	rm -rf ./install_dir

clean:
	-rm -rf ./install_dir
	-rm -rf test
	-rm -rf *.o && rm -rf *.gcno
	-rm -rf *.a && rm -rf *.gcda
	-rm -rf *.info && rm -rf *.gcov
	-rm -rf ./gcov_report
	-rm -rf ./report/
	-rm -rf report.out
	-rm -rf tetris && rm -rf install
	-rm -rf tetris_project.tar.gz
	-rm -rf ./docs/documentation.aux
	-rm -rf ./docs/documentation.dvi
	-rm -rf ./docs/documentation.log
	-rm -rf ./docs/documentation.pdf

test: clean $(EXECUTABLE).a
	$(CC) $(CFLAGS) test.c -L. $(EXECUTABLE).a -lcheck -lncurses -o test

gcov_report: clean $(EXECUTABLE).a
	$(CC) $(GCOVFLAGS) -lncurses test.c $(DIR_GAME)/game_logic.c $(DIR_INTERFACE)/interface.c -o report.out -lm -lcheck -lncurses
	./report.out
	gcov -f test.c
	lcov -t "gcov_report" -o Coverage_Report.info -c -d . --no-external
	genhtml -o ./report Coverage_Report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov
	xdg-open ./report/index-sort-f.html
# open ./report/index-sort-f.html

dist:
	tar -cvzf tetris_project.tar.gz ./gui ./brick_game ./Makefile

dvi: $(DOCS)
	latex -output-directory=./docs ./docs/documentation.tex
	dvipdf ./docs/documentation.dvi ./docs/documentation.pdf
# xdvi ./docs/documentation.dvi