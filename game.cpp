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

/*  Set up the game by:
    - create a normal deck
    - getting number of players
    - name each player
    - draw 3 card per player*/
void Game::setUp() {
    // Validating user's input of number of players
    do {
        std::cout << "NOTE: 17 players MAX (3 cards * 17 players = 51 cards/52 cards)" << endl;
        std::cout << "Enter number of player(s): ";

        // If the user's input is not an integer:
        std::cin >> num_players;
        if (std::cin.fail()) {
            std::cin.clear();
            // Ignore the previous num_players input to take in the player's name
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // consume newline
            std::cout << "Invalid input, please enter an integer: " << endl;
        }

    } while (num_players < 1 || num_players > 17);


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
            insertAtBeginning<Card>(arr_players[i].head, deck.dealOne());
        printListForward(arr_players[i].head);
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
