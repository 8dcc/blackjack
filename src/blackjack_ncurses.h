#include <ncurses.h>

// =============================================================================
// FUNCTIONS
// =============================================================================

// Prints deck in normal mode
void print_deck(card_t* deck) {
    // Show the state of the deck
    for (int n = 0; n < DECK_SIZE; n++) {
        printf("%s(%s)|", n2str(deck[n].number), s2str(deck[n].suit));

        // Newline each suit
        if ((n + 1) % (DECK_SIZE / 4) == 0) putchar('\n');
    }
}

// Prints deck in card mode in 1 line format
void pretty_print_deck(card_t* deck) {
    for (int y = 0; y < DECK_SIZE; y++) {
        print_card_top(2);
    }
    putchar('\n');

    for (int y = 0; y < DECK_SIZE; y++) {
        printf("%s%s %s", CARD_CHAR_Y, s2str(deck[y].suit), CARD_CHAR_Y);
    }
    putchar('\n');

    for (int y = 0; y < DECK_SIZE; y++) {
        if (deck[y].number == 10)
            printf("%s%s%s", CARD_CHAR_Y, n2str(deck[y].number), CARD_CHAR_Y);
        else
            printf("%s %s%s", CARD_CHAR_Y, n2str(deck[y].number), CARD_CHAR_Y);
    }
    putchar('\n');

    for (int y = 0; y < DECK_SIZE; y++) {
        print_card_bottom(2);
    }
    putchar('\n');
}

// Prints deck in card mode in N lines format. Tested with 4, does not work with 8
void pretty_print_deck_rows(card_t* deck, int row_num) {
    const int cards_per_row = DECK_SIZE / row_num;
    card_t rows[row_num][cards_per_row];

    // Move deck into X rows
    int cur_row_n = 0;
    int cur_col_n = 0;
    for (int n = 0; n < DECK_SIZE; n++) {
        rows[cur_row_n][cur_col_n] = deck[n];
        cur_col_n++;

        // 1/4 of the deck, next row
        if ((n + 1) % cards_per_row == 0) {
            cur_col_n = 0;
            cur_row_n++;
        }
    }

    // Print each row
    for (int y = 0; y < row_num; y++) {
        for (int x = 0; x < cards_per_row; x++) {
            print_card_top(2);
        }
        putchar('\n');

        for (int x = 0; x < cards_per_row; x++) {
            printf("%s%s %s", CARD_CHAR_Y, s2str(rows[y][x].suit), CARD_CHAR_Y);
        }
        putchar('\n');

        for (int x = 0; x < cards_per_row; x++) {
            if (rows[y][x].number == 10)        // Remove space if 2 digits
                printf("%s%s%s", CARD_CHAR_Y, n2str(rows[y][x].number), CARD_CHAR_Y);
            else
                printf("%s %s%s", CARD_CHAR_Y, n2str(rows[y][x].number), CARD_CHAR_Y);
        }
        putchar('\n');

        for (int x = 0; x < cards_per_row; x++) {
            print_card_bottom(2);
        }
        putchar('\n');
    }
}

// Default player settings
void init_player(player_t* player, int id, int money) {
    player->id         = id;
    player->money      = money;
    player->bet        = 0;
    player->hitting    = 1;     // Start as true because we want to ask users for input the first time
    player->cards      = 0;
    player->card_value = 0;
    player->hand       = malloc(sizeof(card_t) * MAX_HAND_CARDS);     // Allocate 10 cards for the hand
}

// Initialize the deck with all the cards in order
void clear_deck(card_t* deck) {
    int cur_number = ACE;
    int cur_suit   = DIAMONDS;

    for (int n = 0; n < DECK_SIZE; n++) {
        card_t buff = { cur_number, cur_suit, 0 };      // Start cards with hidden disabled
        deck[n] = buff;

        // We just put an ace, reset number and change suit
        if (cur_number >= KING) {
            cur_number = ACE;
            cur_suit++;
        } else {
            cur_number++;
        }
    }
}

// Shuffle the deck with random positions
void shuffle(card_t* deck) {
    srand(time(NULL));

    for (int n = 0; n < DECK_SIZE; n++) {
        size_t rand_pos = n;
        if (rand() % 2 && n > 0)         // Random position will be smaller
            rand_pos -= rand() % n;
        else                            // or bigger
            rand_pos += rand() % DECK_SIZE - n;

        card_t original = deck[rand_pos];   // Save the old random card
        deck[rand_pos] = deck[n];           // Swap random card with current one
        deck[n] = original;                 // Set current one to stored random
    }
}

// TODO: Define X and Y positions and use them instead of parameters (so we can call it the same way from main)
// Shows the hand
void show_hand(card_t* hand, size_t cards) {
    if (cards < 1) return;      // Don't draw if we don't have cards...

    for (int y = 0; y < cards; y++) {
        print_card_top(2);      // TODO: Do here directly with defined chars
    }
    putchar('\n');

    for (int y = 0; y < cards; y++) {
        if (hand[y].hidden)
            printf("%s%s%s%s", CARD_CHAR_Y, CARD_CHAR_HIDDEN, CARD_CHAR_HIDDEN, CARD_CHAR_Y);     // Show gray chars if card is hidden
        else 
            printf("%s%s %s", CARD_CHAR_Y, s2str(hand[y].suit), CARD_CHAR_Y);
    }
    putchar('\n');

    for (int y = 0; y < cards; y++) {
        if (hand[y].hidden)
            printf("%s%s%s%s", CARD_CHAR_Y, CARD_CHAR_HIDDEN, CARD_CHAR_HIDDEN, CARD_CHAR_Y);     // Show gray chars if card is hidden
        else if (hand[y].number == 10)
            printf("%s%s%s", CARD_CHAR_Y, n2str(hand[y].number), CARD_CHAR_Y);
        else
            printf("%s %s%s", CARD_CHAR_Y, n2str(hand[y].number), CARD_CHAR_Y);
    }
    putchar('\n');

    for (int y = 0; y < cards; y++) {
        print_card_bottom(2);
    }
    putchar('\n');
}

// Move last item to first and shift array
void back_to_front(card_t* deck) {
    card_t back = deck[DECK_SIZE - 1];
    for (int n = DECK_SIZE - 1; n > 0; n--) {
        deck[n] = deck[n-1];
    }
    deck[0] = back;
}

// Move first item to last and shift array
void front_to_back(card_t* deck) {
    card_t front = deck[0];
    for (int n = 0; n < DECK_SIZE; n++) {
        deck[n] = deck[n+1];
    }
    deck[DECK_SIZE - 1] = front;
}

// Will deal the last card of the deck
void deal_card(player_t* player) {
    card_t dealt_card = pDeck[0];

    // Use player->cards for adding a new car (access idx of card number)
    player->hand[player->cards] = dealt_card;
    player->cards++;

    if (dealt_card.number > 1 && dealt_card.number < 11) {
        player->card_value += dealt_card.number;
    } else if (dealt_card.number >= 11) {
        player->card_value += 10;
    } else if (dealt_card.number == 1) {
        if (player->card_value + 11 > 21)
            player->card_value += 1;
        else
            player->card_value += 11;
    } else {
        printf("Error! Incorrect card detected...");
    }

    // Shift deck array
    front_to_back(pDeck);
}

// Prints debug player information
void debug_player(player_t* player) {
    printf("Player ID: %d | Money: %5d | Card number: %d | Hand:\n", player->id, player->money, player->cards);
    show_hand(player->hand, player->cards);
}

// Prints player information for the game
void print_player(player_t* player) {
    if (player->id == 0)    printf("Dealer   | ");
    else                    printf("Player %d | ", player->id);
    
    printf("Money: %5d | Bet: %5d | ", player->money, player->bet);

    if (player->hand[0].hidden)     printf("Total card value: ?\n");
    else                            printf("Total card value: %d\n", player->card_value);

    show_hand(player->hand, player->cards);

    if (!player->hand[0].hidden) {
        if (player->card_value == 21)       printf("Blackjack!\n");
        else if (player->card_value > 21)   printf("Busted!\n");
    }
    
    putchar('\n');
}

// Will read the bet ammount for a player
void read_bet_input(player_t* player) {
    int bet = 0;

    int loop = 1;
    while (loop) {
        printf("Player %d | Place your bet ($%d): ", player->id, player->money);
        scanf("%7d", &bet);

        if (bet < 1 || bet > 9999999)   printf("That is not a valid bet!\n");
        else if (bet > player->money)   printf("You don't have enough money!\n");
        else                            loop = 0;
    }

    player->money -= bet;
    player->bet    = bet;

    putchar('\n');
}

// Read the user input when dealing
void user_deal_option(player_t* player) {
    if (player->card_value == 21) {
        player->hitting = 0;        // Don't ask for input if we have blackjack
        return;
    }

    int selected_option = 0;

    int loop = 1;
    while (loop) {
        printf("Player %d | ", player->id);
        printf(TC_B_WHT "What do you want to do?" TC_NRM " [" TC_B_RED "H" TC_NRM "it/" TC_B_RED "S" TC_NRM "tand/" TC_B_RED "D" TC_NRM "ouble down]: ");

        char input[256];
        scanf("%255s", input);

        switch (input[0]) {
            case 'H':
            case 'h':
                selected_option = 0;
                loop = 0;
                break;
            case 'S':
            case 's':
                selected_option = 1;
                loop = 0;
                break;
            case 'D':
            case 'd':
                if (player->money >= player->bet) {
                    selected_option = 2;
                    loop = 0;
                } else {
                    printf("You don't have enough money!\n");
                }
                break;
            default:
                printf("Error reading option... Try again.\n");
                break;
        }
    }

    // After reading the user input, do what we have to do with the selected option
    switch (selected_option) {
        case 0:     // Hit
            deal_card(player);
            print_player(player);

            if (player->card_value < 21)        // Less than 21, can still hit
                player->hitting = 1;
            else
                player->hitting = 0;

            break;
        case 1:     // Stand
            player->hitting = 0;
            break;
        case 2:     // Double down
            // We made sure the player has money to double down when reading input
            player->hitting = 0;
            player->money -= player->bet;
            player->bet   *= 2;

            deal_card(player);
            print_player(player);

            break;
        default:    // Should never happen
            printf("Error. Wrong option...\n");
            break;
    }

    putchar('\n');      // Newline after input/messages
}

// Keep drawing cards until threshold and print state
void dealer_draw(player_t* dealer) {
    while (dealer->card_value < DEALER_THRESHOLD)
        deal_card(dealer);

    print_player(dealer);
}

// Compare 2 players to check who wins. Keep in mind that if we bust we will lose even if the dealer busts!
void compare_players(player_t* dealer, player_t* player) {
    // We busted or we have less than dealer and dealer didn't bust
    if (player->card_value > 21 || (dealer->card_value <= 21 && player->card_value < dealer->card_value)) {
        printf("Player %d | Dealer wins. You lost: %d", player->id, player->bet);
    // We have the same, push
    } else if (player->card_value == dealer->card_value) {
        printf("Player %d | Push. You recovered: %d", player->id, player->bet);
    // We didn't bust and dealer busted or we have more than dealer
    } else if (dealer->card_value > 21 || player->card_value > dealer->card_value) {
        // Give back bet + profit*1.5 if blackjack
        if (player->card_value == 21) {
            printf("Player %d | You won: %d", player->id, (int)(player->bet * 2.5));
            player->money += (int)(player->bet * 2.5);
        // Give back bet + profit
        } else {
            printf("Player %d | You won: %d", player->id, (int)(player->bet * 2));
            player->money += (int)(player->bet * 2);
        }
    }

    printf(" | Money: %d\n", player->money);
    player->bet = 0;       // Reset bet counter
}

