#include "Game.h"
#include "Player.h"
#include "node.h"
#include "Deck.h"
#include "Card.h"
#include <iostream>
#include <limits>
using namespace std;

Game::Game() : arr_players(nullptr), num_players(0), turn(0) {
    deck.buildStandard52();
    deck.shuffle();
};

Game::~Game() {
    if (arr_players) {
        for (int i = 0; i < num_players; i++) {
            deleteList(arr_players[i].head);
            arr_players[i].head = nullptr;
        }
            delete[] arr_players;
            arr_players = nullptr;
    }

};

// POINT FUNCTION #1: compute one player's points from their hand 
int Game::calculatePoints(Node<Card>* handHead) const {
    int sum = 0;
    int count = 0;

    Node<Card>* cur = handHead;
    while (cur != nullptr && count < 3) {       // Bài Cào uses 3 cards
        sum += cur->data.caoValue();            // A=1, 2..9=value, 10/J/Q/K=0
        cur = cur->next;
        count++;
    }

    return sum % 10; // if sum >= 10, keep only the last digit
}

// POINT FUNCTION #2: compute and store points for all players
void Game::calculatePointsForAllPlayers() {
    for (int i = 0; i < num_players; i++) {
        arr_players[i].points = calculatePoints(arr_players[i].head);
    }
}

// WINNER FUNCTION: returns best score and prints winner(s)
int Game::findWinner() const {
    if (num_players <= 0 || arr_players == nullptr) {
        cout << "No players in the game.\n";
        return -1;
    }

    // Find highest points
    int best = arr_players[0].points;
    for (int i = 1; i < num_players; i++) {
        if (arr_players[i].points > best) {
            best = arr_players[i].points;
        }
    }

    // Print winners (handle ties)
    cout << "\nWinner(s) with " << best << " point(s): ";
    bool first = true;
    for (int i = 0; i < num_players; i++) {
        if (arr_players[i].points == best) {
            if (!first) cout << ", ";
            cout << arr_players[i].name;
            first = false;
        }
    }
    cout << "\n";

    return best;
}

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
    if (arr_players == nullptr || num_players <= 0) {
        cout << "Game not set up yet.\n";
        return;
    }
    // Compute points for all players
    calculatePointsForAllPlayers();

    // Print everyone’s hand + points
    cout << "\n--- Hands ---\n";
    for (int i = 0; i < num_players; i++) {
        // prints: Name: AS 7H QD (points=8)
        arr_players[i].printHand();
    }

    // Find and announce winner(s)
    findWinner();
}
void Game::endGame(){
    cout << "\nGame ended.\n";

}




