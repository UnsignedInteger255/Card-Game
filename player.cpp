#include "Player.h"
#include "Card.h"
#include "Deck.h"

#include "node.h"     

#include <iostream>
using namespace std;

Player::Player(const std::string& n)
    : name(n), head(nullptr), points(0) {}

void Player::setName(const std::string& n) {
    name = n;
}

// Delete all nodes in the player's hand and reset points
void Player::clearHand() {
    deleteList(head);  // deletes every Node<Card> in the hand
    head = nullptr;    
    points = 0;
}

// Draw n cards from deck into player's hand
void Player::draw(Deck& deck, int n) {
    // If you want a "new hand" each time, clear first
    clearHand();

    for (int i = 0; i < n; i++) {
        Card c = deck.dealOne();
        insertAtEnd(head, c);
    }

    computePoints();
}

// Bài Cào points: A=1, 2..9=value, 10/J/Q/K=0 (already inside Card::caoValue)
// Total points = (sum of 3 cards) % 10
void Player::computePoints() {
    int sum = 0;
    int count = 0;

    Node<Card>* cur = head;
    while (cur != nullptr && count < 3) {     // only count first 3 cards
        sum += cur->data.caoValue();
        cur = cur->next;
        count++;
    }

    points = sum % 10;
}

// Print player's hand + points
void Player::printHand() const {
    cout << name << ": ";

    const Node<Card>* cur = head;
    while (cur != nullptr) {
        cout << cur->data;
        if (cur->next != nullptr) cout << " ";
        cur = cur->next;
    }

    cout << " (points=" << points << ")\n";
}
