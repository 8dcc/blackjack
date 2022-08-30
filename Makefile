
CC=gcc
CFLAGS=-Wall

all: 		blackjack
blackjack:	blackjack.out
ncurses:	blackjack_ncurses.out

blackjack.out: src/*
	$(CC) $(CFLAGS) -o $@ src/main.c

# https://stackoverflow.com/a/35163301/11715554
blackjack_ncurses.out: src/*
	$(CC) $(CFLAGS) -o $@ src/main.c -lncursesw

clean:
	rm *.out
