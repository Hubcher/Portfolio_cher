CC = gcc 
CFLAGS = -Wall -Wextra -Werror -std=c11 -pedantic

CAT = s21_cat.c
TABLE = catFlags.c

all: s21_cat test

s21_cat:
	rm -rf s21_cat
	$(CC) $(CAT) $(TABLE) $(CFLAGS)  -o s21_cat

test:
	rm -rf s21_cat
	$(CC) $(CAT) $(TABLE) $(CFLAGS)  -o ./s21_cat
	chmod +x testcat.sh
	./testcat.sh

clean:
	rm -rf s21_cat
	rm -rf *.o
	rm -rf *.a
