CC=g++
CFLAGS=-Wall -Werror -Wextra -pthread -std=c++17 -lstdc++ 
TEST_FLAGS=-lgtest

VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --tool=memcheck --show-reachable=yes

LIBRARY = s21_containers_oop.a
PROGRAM = test

TESTS_DIR = tests
TEST_SRC = $(wildcard $(TESTS_DIR)/*.cpp)
TEST_OBJ = $(TEST_SRC:.cpp=.o)

LIB_DIR = containers
LIB_SRC = $(wildcard $(LIB_DIR)/*.cpp)
LIB_OBJ = $(LIB_SRC:.cpp=.o)

all: $(LIBRARY) $(PROGRAM)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBRARY): $(LIB_OBJ)
	ar rcs $(LIBRARY) $(LIB_OBJ)
	ranlib $(LIBRARY)

$(PROGRAM): $(LIBRARY) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ) $(LIBRARY) -o $(PROGRAM) $(TEST_FLAGS)
	./$(PROGRAM) || true

valgrind: $(PROGRAM)
	valgrind $(VALGRIND_FLAGS) ./$(PROGRAM)

style_check:
	find . -type f -name "*.cpp" -exec clang-format -n -style=Google {} \;
	find . -type f -name "*.h" -exec clang-format -n -style=Google {} \;

style_fix:
	find . -type f -name "*.cpp" -exec clang-format -i -style=Google {} \;
	find . -type f -name "*.h" -exec clang-format -i -style=Google {} \;

clean:
	rm -rf $(LIB_OBJ) $(TEST_OBJ) $(LIBRARY) $(PROGRAM)

.PHONY: all test clean