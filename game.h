#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "Player.h"
#include "Deck.h"

template <typename T> class Node;
class Card;

class Game {
    private:
    // POINT FUNCTION #1: compute one player's points from their hand
    int calculatePoints(Node<Card>* handHead) const;

    // POINT FUNCTION #2: compute and store points for all players
    void calculatePointsForAllPlayers();

    // WINNER FUNCTION: returns best score and prints winner(s)
    int findWinner() const;

    public:
        // Array of players
        Player* arr_players;
        int num_players;

        // Deck of cards
        Deck deck;

        // Current turn
        int turn;

        // Constructor
        Game();

        // Destructor
        ~Game();

        // Game setup
        void setUp();
        void playGame();
        void endGame();
};
#endif // GAME_H_INCLUDED
