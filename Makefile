
CC=gcc
CFLAGS=-Wall

.PHONY: clean all blackjack ncurses debug

all: 		blackjack
blackjack:	blackjack.out
ncurses:	blackjack_ncurses.out

debug:
	$(eval CFLAGS += -g)

blackjack.out: src/*
	$(CC) $(CFLAGS) -o $@ src/main.c

# https://stackoverflow.com/a/35163301/11715554
blackjack_ncurses.out: src/*
	$(CC) $(CFLAGS) -o $@ src/main.c -DUSE_NCURSES -lncursesw

clean:
	rm *.out
