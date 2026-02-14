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
    void Game::setUp() {
        // Validating user's input of number of players
        do {
            cout << "NOTE: 17 players MAX (3 cards * 17 players = 51 cards/52 cards)";
            cout << "Enter number of player(s): ";
            cin >> num_players;
        } while (num_players < 1 || num_players > 17);

        // Give each player's name and then deal 3 cards;
        for (int i = 0; i < num_players; i++) {
            string name;
            cout << "Enter player " << i+1 << "'s name: ";
            cin >> name;
            arr_players[i].name = name;

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



