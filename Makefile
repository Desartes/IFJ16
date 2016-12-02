CC = gcc

OPT = -O

CFLAGS = -std=c99 -Wall -Wextra -pedantic

all:main.c
	$(CC) $(OPT) $(CFLAGS) err.h err.c ial.h ial.c main.c -o main
	
clean:
	rm -f main