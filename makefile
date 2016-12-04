CC = gcc
OPT = -O2
CFLAGS = -std=c99 -Wall -Wextra -pedantic
FILES = err.c err.h scanner.c scanner.h
main: $(FILES)
	$(CC) $(OPT) $(CFLAGS) $(FILES)  -o main
clean:
	rm -f main
