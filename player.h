#include <iostream>

#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

// Forward declarations
template <typename T> class Node;
class Card;

class Player {
    public:
        // Player's name
        std::string name;
        // Player's hand
        Node<Card>* head;
        int points;

        // Constructor
        Player() : name(""), head(nullptr), points(0) {};
};

#endif // PLAYER_H_INCLUDED
