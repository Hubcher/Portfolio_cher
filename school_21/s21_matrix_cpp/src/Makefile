CC = g++
CFLAGS = -std=c++17 -Wall -Werror -Wextra -g
GCOVFLAGS = -fprofile-arcs -ftest-coverage --coverage

TEST_DIR = ./tests
OBJ_DIR = ./obj

TARGET = s21_matrix_oop.a

SRC_FILES = $(wildcard ./*.cc)
TEST_FILES = $(wildcard $(TEST_DIR)/*.cc)
OBJ_FILES = $(patsubst ./%.cc, $(OBJ_DIR)/%.o, $(SRC_FILES)) \
            $(patsubst $(TEST_DIR)/%.cc, $(OBJ_DIR)/%.o, $(TEST_FILES))

all: clean $(TARGET) test 

$(TARGET): $(OBJ_FILES)
	ar rcs $(TARGET) $^

matrix_oop_exe: $(TARGET)
	$(CC) $(CFLAGS) $(GCOVFLAGS) -o $@ $^ -lgtest -lgtest_main -pthread


$(OBJ_DIR)/%.o: ./%.cc
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(GCOVFLAGS) -c $< -o $@
	

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cc
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(GCOVFLAGS) -I$(GTEST_DIR)/include -c $< -o $@

test: clean matrix_oop_exe
	./matrix_oop_exe --gtest_brief=1

clean:
	rm -rf ./obj
	rm -rf ./tests/*.o
	rm -rf *.out
	rm -rf *.o
	rm -rf *.a
	rm -rf *.gcno
	rm -rf *.gch
	rm -rf *.gcda
	rm -rf *.gcov
	rm -rf *.info
	rm -rf *.html
	rm -rf *.css
	rm -rf test
	rm -rf gcov_test
	rm -rf gcov_report.info
	rm -rf test report
	rm -rf *exe


# gcov_report: test
#	gcovr -r . --html --html-details -o report.html
#	xdg-open ./report.html