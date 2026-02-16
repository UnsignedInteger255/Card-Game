#include <iostream>
#include "game.h"
#include "Deck.h"
#include "node.h"
#include "player.h"
#include "Card.h"
using namespace std;

int main() {
    Game new_game;
    new_game.setUp();
    new_game.playGame();
    new_game.endGame()

    return 0;
}

