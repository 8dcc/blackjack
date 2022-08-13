
#define DECK_SIZE 52

// Figures
enum {
    ACE = 1,
    JACK = 11,
    QUEEN,
    KING
};

// Suits
enum {
    DIAMONDS = 0,
    CLUBS,
    HEARTS,
    SPADES
};

// Card
typedef struct Card {
    int number;
    int suit;
} card_t;

// =============================================================================
// FUNCTIONS
// =============================================================================

char* n2str(int number) {
    switch (number) {
        case 1:     return "A";      break;
        case 2:     return "2";      break;
        case 3:     return "3";      break;
        case 4:     return "4";      break;
        case 5:     return "5";      break;
        case 6:     return "6";      break;
        case 7:     return "7";      break;
        case 8:     return "8";      break;
        case 9:     return "9";      break;
        case 10:    return "10";     break;
        case 11:    return "J";      break;
        case 12:    return "Q";      break;
        case 13:    return "K";      break;
        default:    break;
    }

    return "";
}

char* s2str(int suit) {
    switch (suit) {
        case DIAMONDS:      return "D";     break;
        case CLUBS:         return "C";     break;
        case HEARTS:        return "H";     break;
        case SPADES:        return "S";     break;
        default:            break;
    }

    return "";
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
