
// =============================================================================
// HELPERS
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
        case DIAMONDS:      return "\x4";     break;
        case CLUBS:         return "\x5";     break;
        case HEARTS:        return "\x3";     break;
        case SPADES:        return "\x6";     break;
        default:            break;
    }

    return "";
}

