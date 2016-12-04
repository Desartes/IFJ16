CC = gcc
OPT = -O2
CFLAGS = -std=c99 -Wall -Wextra -pedantic

main: err.c err.h scanner.c scanner.h
	$(CC) $(OPT) $(CFLAGS) err.c err.h scanner.c scanner.h -o sc_main
clean:
	rm -f sc_main
