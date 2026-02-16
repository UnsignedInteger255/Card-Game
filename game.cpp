#include <iostream>
#include <string>
#include "player.h"
#include "deck.h"
#include "node.h"
#include "Card.h"
#include "game.h"

Game::Game() : arr_players(nullptr), num_players(0), turn(0) {
    deck.buildStandard52();
    deck.shuffle();
};

Game::~Game() {
    if (arr_players) {
        for (int i = 0; i < num_players; i++) {
            deleteList(arr_players[i].head);
        }
            delete[] arr_players;
    }
};

/*  Set up the game by:
    - create a normal deck
    - getting number of players
    - name each player
    - draw 3 card per player*/

// POINT FUNCTION #1: calculate one player's Bài Cào points from their 3-card hand
int Game::calculatePointsForPlayer(Node<Card>* handHead) const {
    int sum = 0;
    int count = 0;

    Node<Card>* cur = handHead;
    while (cur != nullptr && count < 3) {
        sum += cur->data.caoValue();
        cur = cur->next;
        count++;
    }

    return sum % 10; // last digit
}

// POINT FUNCTION #2: calculate points for all players and store into arr_players[i].points
void Game::calculatePointsForAllPlayers() {
    for (int i = 0; i < num_players; i++) {
        arr_players[i].points = calculatePointsForPlayer(arr_players[i].head);
    }
}

// WINNER FUNCTION: prints winner(s) (ties allowed)
void Game::findWinner() const {
    int best = -1;

    for (int i = 0; i < num_players; i++) {
        if (arr_players[i].points > best) best = arr_players[i].points;
    }

    cout << "Best score: " << best << "\nWinner(s): ";
    bool first = true;

    for (int i = 0; i < num_players; i++) {
        if (arr_players[i].points == best) {
            if (!first) cout << ", ";
            cout << arr_players[i].name;
            first = false;
        }
    }
    cout << "\n";
}
void Game::setUp() {
    // Validating user's input of number of players
    do {
        cout << "NOTE: 17 players MAX (3 cards * 17 players = 51 cards/52 cards)";
        cout << "Enter number of player(s): ";
        
        cin >> num_players;
        // Ignore the previous num_players input to take in the player's name
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // consume newline

        
    } while (num_players < 1 || num_players > 17);

    // Allocate array of players
    arr_players = new Player[num_players];

    
    // Give each player's name and then deal 3 cards;
    for (int i = 0; i < num_players; i++) {
        std::string player_name;
        std::cout << "Enter player " << i+1 << "'s name: ";
        
        std::getline(std::cin, player_name);
        arr_players[i].name = player_name;

        // Deal 3 cards
        for (int j = 0; j < 3; j++) {
            insertAtBeginning<Card>(arr_players[i].head, deck.dealOne());
        }
    }
}

// To play the game
void Game::playGame() {

}

void Game::endGame(){}




