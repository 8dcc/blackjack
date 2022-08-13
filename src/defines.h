
// =============================================================================
// DEFINES
// =============================================================================

#define DECK_SIZE 52
#define MAX_HAND_CARDS 10
#define DEALER_MONEY 20000
#define PLAYER_MONEY 5000

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

// =============================================================================
// STRUCTS
// =============================================================================

// Card / Deck
typedef struct Card {
    int number;
    int suit;
    int hidden;
} card_t;


// Player
typedef struct Player {
    int id;
    int money;
    int cards;          // Number of cards
    int card_value;     // Total value of cards
    card_t* hand;
} player_t;
