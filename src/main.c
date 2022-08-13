#include <stdio.h>
#include "blackjack.h"

int main(int argc, char** argv) {
    card_t deck[DECK_SIZE];         // Create the main deck
    clear_deck(&deck[0]);           // Initialize it

    // Show the state of the deck
    for (int n = 0; n < DECK_SIZE; n++) {
        printf("%s(%s)|", n2str(deck[n].number), s2str(deck[n].suit));

        // Newline each suit
        if ((n + 1) % (DECK_SIZE / 4) == 0) putchar('\n');
    }

    // @todo: Shuffle

    return 0;
}

