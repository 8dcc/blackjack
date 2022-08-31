
// =============================================================================
// DEFINES
// =============================================================================

#define DECK_SIZE        52
//#define DECK_NUM 1
#define MAX_HAND_CARDS   10         // For allocating space
#define DEALER_THRESHOLD 17         // Won't hit from this card
#define PLAYER_NUM       2          // Dealer counts as player
#define DEALER_MONEY     20000
#define PLAYER_MONEY     5000

// Using ncurses on linux, comment this if you want to use the normal mode on linux
#ifdef __unix__
#define USE_NCURSES
#endif

// Define positions even if not using ncurses
#define DEF_HAND_X      1                   // Default X and Y positions
#define DEF_HAND_Y      1
#define DEF_HAND_Y_M    1                   // Top margin
#define CARD_H          4                            // Space that each hand takes
#define HAND_H DEF_HAND_Y_M + CARD_H + 2    // First line + cards + busted/bj space + newline

// Use simpler characters for cards
//#define SIMPLE_CHARS

#ifdef SIMPLE_CHARS
#define CARD_CHAR_X         "-"
#define CARD_CHAR_Y         "|"
#define CARD_CHAR_TL        "+"
#define CARD_CHAR_TR        "+"
#define CARD_CHAR_BL        "+"
#define CARD_CHAR_BR        "+"
#define CARD_CHAR_HIDDEN    "#"
#elif _WIN32                    // Strings gave some problems on windows
#define CARD_CHAR_X         "\xC4"
#define CARD_CHAR_Y         "\xB3"
#define CARD_CHAR_TL        "\xDA"
#define CARD_CHAR_TR        "\xBF"
#define CARD_CHAR_BL        "\xC0"
#define CARD_CHAR_BR        "\xD9"
#define CARD_CHAR_HIDDEN    "\xB1"
#else                           // __unix__
#define CARD_CHAR_X         "─"
#define CARD_CHAR_Y         "│"
#define CARD_CHAR_TL        "┌"
#define CARD_CHAR_TR        "┐"
#define CARD_CHAR_BL        "└"
#define CARD_CHAR_BR        "┘"
#define CARD_CHAR_HIDDEN    "▒"
#endif

// =============================================================================
// ENUMS
// =============================================================================

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
    int hand_x, hand_y; // For ncurses
    int money;
    int bet;
    int hitting;
    int cards;          // Number of cards
    int card_value;     // Total value of cards
    card_t* hand;
} player_t;

// =============================================================================
// GLOBALS
// =============================================================================

card_t deck[DECK_SIZE];             // Create the main deck
card_t* pDeck = &deck[0];           // Pointer for commodity
