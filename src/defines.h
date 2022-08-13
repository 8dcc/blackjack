
// =============================================================================
// DEFINES
// =============================================================================

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
