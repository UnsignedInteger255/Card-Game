#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <string>


template <typename T> class Node;
class Card;
class Deck;

class Player {
public:
    std::string name;   // player's name
    Node<Card>* head;   // head of linked list representing player's hand
    int points;         // Bài Cào points (0..9)

    // Constructor
    Player(const std::string& n = "");

    void setName(const std::string& n);

    void clearHand();                 // delete all nodes in hand, reset points
    void draw(Deck& deck, int n = 3); // draw n cards from deck (default 3)

    // Scoring + display
    void computePoints();             // points = (sum caoValue of cards) % 10
    void printHand() const;           // prints: Name: AS 7H QD (points=8)
};

#endif // PLAYER_H_INCLUDED
