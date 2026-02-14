#include "Card.h"
#include <stdexcept>
using namespace std;

// Constructor: initializes rank/suit using an initializer list.
Card::Card(int rank, Suit suit) : rank_(rank), suit_(suit) {
    if (rank_ < 1 || rank_ > 13) {
        // Throwing an exception makes the error obvious immediately,
        // instead of letting invalid cards silently break the game.
        throw std::invalid_argument("Card rank must be 1-13");
    }
}

// Simple getters (const because they do not modify the Card).
int Card::rank() const { 
    return rank_; 
}
Card::Suit Card::suit() const { 
    return suit_; 
}

// Bài Cào scoring rule:
// A counts as 1, 2..9 count as their face value, 10/J/Q/K count as 0.
// (Total score in the game is usually sum % 10.)
int Card::caoValue() const {
    if (rank_ == 1) 
        return 1;
    if (rank_ >= 2 && rank_ <= 9) 
        return rank_;
    return 0; // 10/J/Q/K
}

// Helper: convert rank number into printable text.
// Face cards and Ace use letters; all other ranks use their numeric string.
string Card::rankToString(int r) {
    if (r == 1) 
        return "A";
    if (r == 11) 
        return "J";
    if (r == 12) 
        return "Q";
    if (r == 13) 
        return "K";
    return std::to_string(r);
}


// Helper: convert suit enum into a short printable label.
string Card::suitToString(Suit s) {
    switch (s) {
        case Suit::Clubs: 
            return "C";
        case Suit::Diamonds: 
            return "D";
        case Suit::Hearts: 
            return "H";
        case Suit::Spades: 
            return "S";
    }
    throw invalid_argument("Invalid suit value");
}

//Returns a compact string like "AS", "10H", "KD".
string Card::toString() const {
    return rankToString(rank_) + suitToString(suit_);
}

ostream& operator<<(ostream& os, const Card& c) {
    os << c.toString();
    return os;
}
