
CC=gcc
CFLAGS=-Wall

all: 		blackjack
blackjack:	blackjack.out
ncurses:	blackjack_ncurses.out

blackjack.out: src/*
	$(CC) $(CFLAGS) -o $@ src/main.c

blackjack_ncurses.out: src/*
	$(CC) $(CFLAGS) -o $@ src/main.c -lncurses

clean:
	rm *.out
