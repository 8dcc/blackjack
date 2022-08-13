
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

void print_card_top(int w) {
    putchar(218);
    for (int n = 0; n < w; n++)
        putchar(196);
    putchar(191);
}

void print_card_bottom(int w) {
    putchar(192);
    for (int n = 0; n < w; n++)
        putchar(196);
    putchar(217);
}

// Prints deck in card mode in 1 line format
void pretty_print_deck(card_t* deck) {
    for (int y = 0; y < DECK_SIZE; y++) {
        print_card_top(2);
    }
    putchar('\n');

    for (int y = 0; y < DECK_SIZE; y++) {
        printf("%c%s %c", 179, s2str(deck[y].suit), 179);
    }
    putchar('\n');

    for (int y = 0; y < DECK_SIZE; y++) {
        if (deck[y].number == 10)
            printf("%c%s%c", 179, n2str(deck[y].number), 179);
        else
            printf("%c %s%c", 179, n2str(deck[y].number), 179);
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
            printf("%c%s %c", 179, s2str(rows[y][x].suit), 179);
        }
        putchar('\n');

        for (int x = 0; x < cards_per_row; x++) {
            if (rows[y][x].number == 10)        // Remove space if 2 digits
                printf("%c%s%c", 179, n2str(rows[y][x].number), 179);
            else
                printf("%c %s%c", 179, n2str(rows[y][x].number), 179);
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
    player->cards      = 0;
    player->card_value = 0;
    player->hand       = malloc(sizeof(card_t) * MAX_HAND_CARDS);     // Allocate 10 cards for the hand
}

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

// https://stackoverflow.com/questions/6127503/shuffle-array-in-c
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

// Shows the hand
void show_hand(card_t* hand, size_t cards) {
    for (int y = 0; y < cards; y++) {
        print_card_top(2);
    }
    putchar('\n');

    for (int y = 0; y < cards; y++) {
        if (hand[y].hidden)
            printf("%c%c%c%c", 179, 177, 177, 179);     // Show gray chars if card is hidden
        else 
            printf("%c%s %c", 179, s2str(hand[y].suit), 179);
    }
    putchar('\n');

    for (int y = 0; y < cards; y++) {
        if (hand[y].hidden)
            printf("%c%c%c%c", 179, 177, 177, 179);     // Show gray chars if card is hidden
        else if (hand[y].number == 10)
            printf("%c%s%c", 179, n2str(hand[y].number), 179);
        else
            printf("%c %s%c", 179, n2str(hand[y].number), 179);
    }
    putchar('\n');

    for (int y = 0; y < cards; y++) {
        print_card_bottom(2);
    }
    putchar('\n');
}

// Last item to first and shift array
void back_to_front(card_t* deck) {
    card_t back = deck[DECK_SIZE - 1];
    for (int n = DECK_SIZE - 1; n > 0; n--) {
        deck[n] = deck[n-1];
    }
    deck[0] = back;
}

// First item to last and shift array
void front_to_back(card_t* deck) {
    card_t front = deck[0];
    for (int n = 0; n < DECK_SIZE; n++) {
        deck[n] = deck[n+1];
    }
    deck[DECK_SIZE - 1] = front;
}

// Will deal the last card of the deck
void deal_card(card_t* deck, player_t* player) {
    card_t dealt_card = deck[0];

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
    front_to_back(deck);
}

// Prints debug player information
void debug_player(player_t* player) {
    printf("Player ID: %d | Money: %5d | Card number: %d | Hand:\n", player->id, player->money, player->cards);
    show_hand(player->hand, player->cards);
}

// Prints player information for the game
void print_player(player_t* player) {
    if (player->id == 0)    printf("Dealer | ");
    else                    printf("Player %d | ", player->id);
    
    printf("Money: %5d | ", player->money);

    if (player->hand[0].hidden)     printf("Total card value: ?\n");
    else                            printf("Total card value: %d\n", player->card_value);

    show_hand(player->hand, player->cards);
    putchar('\n');
}

void user_deal_option(player_t* player) {
    printf(TC_B_WHT "What do you want to do?" TC_NRM " [" TC_B_RED "H" TC_NRM "it/" TC_B_RED "S" TC_NRM "tand/" TC_B_RED "D" TC_NRM "ouble down]: ");

    char* input[256];
    scanf("%255s", input);
}

