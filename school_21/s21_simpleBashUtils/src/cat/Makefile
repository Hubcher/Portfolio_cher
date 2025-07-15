CC = gcc 
CFLAGS = -Wall -Wextra -Werror -std=c11 -pedantic

CAT = s21_cat.c
TABLE = catFlags.c

s21_cat:
	rm -rf s21_cat
	$(CC) $(CAT) $(TABLE) $(CFLAGS)  -o s21_cat

test:
	rm -rf s21_cat
	$(CC) $(CAT) $(TABLE) $(CFLAGS)  -o ./test_cat/s21_cat

clean:
	rm -rf s21_cat
	rm -rf *.o
	rm -rf *.a
	rm -rf ./test_cat/s21_cat
