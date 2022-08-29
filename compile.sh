#!/bin/bash

CFLAGS="-Wall"
BIN="blackjack.out"
NCURSES=""

# If first argument is ncurses, add ncurses for the linker
if [[ $1 == "ncurses" ]]; then
    NCURSES="-lncurses"
fi

# Compile the file
gcc -o $BIN $CFLAGS src/main.c $NCURSES

echo "Compiled as $BIN"
exit 0;
