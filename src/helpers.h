
// =============================================================================
// HELPERS
// =============================================================================

char* n2str(int number) {
#ifdef USE_NCURSES
    switch (number) {
        case 1:     return "A";     break;
        case 2:     return "2";     break;
        case 3:     return "3";     break;
        case 4:     return "4";     break;
        case 5:     return "5";     break;
        case 6:     return "6";     break;
        case 7:     return "7";     break;
        case 8:     return "8";     break;
        case 9:     return "9";     break;
        case 10:    return "10";    break;
        case 11:    return "J";     break;
        case 12:    return "Q";     break;
        case 13:    return "K";     break;
        default:    break;
    }
#else
    switch (number) {
        case 1:     return TC_B_WHT "A"  TC_NRM;    break;
        case 2:     return TC_B_WHT "2"  TC_NRM;    break;
        case 3:     return TC_B_WHT "3"  TC_NRM;    break;
        case 4:     return TC_B_WHT "4"  TC_NRM;    break;
        case 5:     return TC_B_WHT "5"  TC_NRM;    break;
        case 6:     return TC_B_WHT "6"  TC_NRM;    break;
        case 7:     return TC_B_WHT "7"  TC_NRM;    break;
        case 8:     return TC_B_WHT "8"  TC_NRM;    break;
        case 9:     return TC_B_WHT "9"  TC_NRM;    break;
        case 10:    return TC_B_WHT "10" TC_NRM;    break;
        case 11:    return TC_B_WHT "J"  TC_NRM;    break;
        case 12:    return TC_B_WHT "Q"  TC_NRM;    break;
        case 13:    return TC_B_WHT "K"  TC_NRM;    break;
        default:    break;
    }
#endif

    return "";
}

char* s2str(int suit) {
#ifdef USE_NCURSES              // TODO: ncurses colors
    switch (suit) {
        case DIAMONDS:      return "♦";     break;
        case CLUBS:         return "♣";     break;
        case HEARTS:        return "♥";     break;
        case SPADES:        return "♠";     break;
        default:            break;
    }
#elif SIMPLE_CHARS
    switch (suit) {
        case DIAMONDS:      return TC_B_RED "D" TC_NRM;     break;
        case CLUBS:         return TC_B_NRM "C" TC_NRM;     break;
        case HEARTS:        return TC_B_RED "H" TC_NRM;     break;
        case SPADES:        return TC_B_NRM "S" TC_NRM;     break;
        default:            break;
    }
#elif _WIN32                    // Put hex char for windows
    switch (suit) {
        case DIAMONDS:      return TC_B_RED "\x04" TC_NRM;     break;
        case CLUBS:         return TC_B_NRM "\x05" TC_NRM;     break;
        case HEARTS:        return TC_B_RED "\x03" TC_NRM;     break;
        case SPADES:        return TC_B_NRM "\x06" TC_NRM;     break;
        default:            break;
    }
#else                           // Hardcoded chars for __unix__
    switch (suit) {
        case DIAMONDS:      return TC_B_RED "♦" TC_NRM;     break;
        case CLUBS:         return TC_B_NRM "♣" TC_NRM;     break;
        case HEARTS:        return TC_B_RED "♥" TC_NRM;     break;
        case SPADES:        return TC_B_NRM "♠" TC_NRM;     break;
        default:            break;
    }
#endif

    return "";
}

void separator() {
#ifndef USE_NCURSES
    printf(TC_B_WHT "======================================================================================\n\n" TC_NRM);
#endif
}
