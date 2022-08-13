
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
    for (int col = 0; col < DECK_SIZE; col++) {
        putchar(218);
        putchar(196);
        putchar(196);
        putchar(191);
    }
    putchar('\n');

    for (int col = 0; col < DECK_SIZE; col++) {
        printf("%c%s %c", 179, s2str(deck[col].suit), 179);
    }
    putchar('\n');

    for (int col = 0; col < DECK_SIZE; col++) {
        if (deck[col].number == 10)
            printf("%c%s%c", 179, n2str(deck[col].number), 179);
        else
            printf("%c %s%c", 179, n2str(deck[col].number), 179);
    }
    putchar('\n');

    for (int col = 0; col < DECK_SIZE; col++) {
        putchar(192);
        putchar(196);
        putchar(196);
        putchar(217);
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
            putchar(218);
            putchar(196);
            putchar(196);
            putchar(191);
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
            putchar(192);
            putchar(196);
            putchar(196);
            putchar(217);
        }
        putchar('\n');
    }
}

void clear_deck(card_t* deck) {
    int cur_number = ACE;
    int cur_suit   = DIAMONDS;

    for (int n = 0; n < DECK_SIZE; n++) {
        card_t buff = { cur_number, cur_suit };
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
