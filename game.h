#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <string>
#include "player.h"
#include "Deck.h"
#include "node.h"
#include "Card.h"

class Game {
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
    int endGame();

    // Card distribution
    void dealEachPlayer(int n = 3);
    void returnToDeck();
};

#endif // GAME_H_INCLUDED

