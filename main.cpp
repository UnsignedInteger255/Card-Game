#include <iostream>
#include "game.h"

int main() {

    Game game;        // creates deck, builds + shuffles (in Game constructor)
    game.setUp();     // ask #players, names, deal 3 cards each
    game.playGame();  // calculate points, print hands, print winner(s)
    game.endGame();   // optional ending message


    return 0; // success
}
