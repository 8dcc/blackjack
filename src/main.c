#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "defines.h"
#include "helpers.h"
#include "blackjack.h"

int main(int argc, char** argv) {
    card_t deck[DECK_SIZE];         // Create the main deck
    card_t* deck_p = &deck[0];      // Pointer for commodity

    clear_deck(deck_p);             // Initialize it
    pretty_print_deck_rows(deck_p, 4);

    printf("\n");

    shuffle(deck_p);
    pretty_print_deck_rows(deck_p, 4);

    return 0;
}

