
CC=gcc
CFLAGS=-Wall
BIN=bin/blackjack.out

all: blackjack

blackjack: src/*.c
	$(CC) $(CFLAGS) -o $(BIN) src/main.c

ncurses: src/*.c
	$(CC) $(CFLAGS) -o $(BIN) src/main.c -lncurses

clean: bin/*.out
	# Add obj folder if needed
	rm $<
