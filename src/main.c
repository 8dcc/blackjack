#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "lib/colors.h"
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

    // Bets
    read_bet_input(&player1);

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


    // Ask player for deal
    int dealing = 1;
    while (dealing) {
        dealing = 0;        // Reset to false, will be set to true if we need to deal

        separator();

        if (player1.hitting) user_deal_option(deck_p, &player1);        // Check the first time so we only ask the ones that just draw a card
        if (player1.hitting) dealing = 1;                               // Check again because the value will change depending on the input
    }

    // Dealer card unhides and picks cards
    separator();
    dealer.hand[0].hidden = 0;
    dealer_draw(deck_p, &dealer);           // Draw til thresold and print_player()
    print_player(&player1);

    // Bet outcome
    compare_players(&dealer, &player1);

    return 0;
}

