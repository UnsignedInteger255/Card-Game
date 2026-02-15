#include <iostream>
#include <string>
#include "player.h"
#include "deck.h"
#include "node.h"
#include "Card.h"
#include "game.h"

// Constructor
Game::Game() : arr_players(nullptr), num_players(0), turn(0) {
    deck.buildStandard52();
    deck.shuffle();
};

// Destrucor
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

/*  There are three return code once the game end:
[0]. Ending the game, and start a new game
[1]. Restart the same game
[2]. Ending the game */
int Game::endGame(){
    int input;
    cout << "Game Over" << endl;
    cout << "Do You Want To Play Again?\t[Enter number]" << endl;
    cout << "[0]. Yes, but with different number of players." << endl;
    cout << "[1]. Yes, restart the same game." << endl;
    cout << "[2]. No, terminate program." << endl;
    do {
        cout << "Input: ";
        if (!(cin >> input)) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid Input, please try again (valid inputs: 0, 1, 2)." << endl;
            continue;
        }

        if (input != 0 && input != 1 && input != 2) {
            cout << "Invalid Input, please try again (valid inputs: 0, 1, 2).";
        }
    } while (input != 0 && input != 1 && input != 2);
    return input;
}

// Card distribution
// Deal each player n card, default n is 3
void Game::dealEachPlayer(int n) {
    for (int i = 0; i < num_players; i++) {
        for (int j = 0; j < n; j++)
            insertAtBeginning<Card>(arr_players[i].hand, deck.dealOne());
    }
}
// Return all players' cards to deck
void Game::returnToDeck() {
    // For each player:
    for (int i = 0; i < num_players; i++) {
        // 1. Go through each player's cards
        Node<Card>* current = arr_players[1].head;
        while (current != nullptr) {
            // 2. Add that player's cards back to the deck
            insertAtBeginning<Card>(deck.head, current->data);

            Node<Card>* temp = current;
            current = current->next;
            /* 3. Delete that player's cards,
             effectively returning those cards back to the deck*/
            delete temp;
        }
    }
}
