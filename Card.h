#ifndef CARD_H 
#define CARD_H

#include <string>
#include <ostream>

// Card represents a standard playing card with a rank and suit.
// Rank uses 1-13: 1=A, 11=J, 12=Q, 13=K.
class Card {
public:
    enum class Suit { Clubs, Diamonds, Hearts, Spades };

    Card(int rank = 1, Suit suit = Suit::Spades);

    int rank() const;
    Suit suit() const;

    // Bài Cào scoring rule:
    // A=1, 2..9 = face value, 10/J/Q/K = 0
    int caoValue() const;

    // Convert card to string like "AS", "10H", "KD"
    std::string toString() const;

private:
    int rank_;   // 1 - 13
    Suit suit_;  // one of the Suit enum values

    // Helpers for toString()
    static std::string rankToString(int r);
    static std::string suitToString(Suit s);
};

// Enables: std::cout << card;
// Needed because linked list prints with: cout << node->data;
std::ostream& operator<<(std::ostream& os, const Card& c);

#endif
