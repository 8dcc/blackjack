#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "defines.h"
#include "helpers.h"
#include "blackjack.h"

int main(int argc, char** argv) {
    card_t deck[DECK_SIZE];             // Create the main deck
    card_t* deck_p = &deck[0];          // Pointer for commodity

    clear_deck(deck_p);                 // Initialize it
    shuffle(deck_p);                    // Shuffle the deck

    player_t dealer;
    init_player(&dealer, 0, DEALER_MONEY);
    player_t player1;
    init_player(&player1, 1, PLAYER_MONEY);

    //pretty_print_deck(deck_p);

    // First deal initial cards
    deal_card(deck_p, &player1);
    deal_card(deck_p, &dealer);
    dealer.hand[0].hidden = 1;      // First dealer card is hidden
    deal_card(deck_p, &player1);
    deal_card(deck_p, &dealer);

    // Print player information after initial dealing
    print_player(&dealer);
    print_player(&player1);

    return 0;
}

