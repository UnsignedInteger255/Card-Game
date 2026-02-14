#include <iostream>
#include "node.h"
#include "game.cpp"
using namespace std;

int main() {
    Game* new_game = new Game();
    new_game->setUp();
    return 0;
}
