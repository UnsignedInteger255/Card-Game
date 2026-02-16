
#include <vector>
#include <random>
#include <algorithm>
#include <stdexcept>
#include <iostream>

#include "node.h"
#include "Deck.h"

//Helper functions

// remove and return top card (updates head pointer)
static Card popFront(Node<Card>*& head) {
    if (head == nullptr) {
        throw std::runtime_error("Cannot deal from an empty deck");
    }

    Node<Card>* temp = head;
    Card value = temp->data;

    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    }

    delete temp;
    return value;
}

// count nodes in the list
static int listSize(Node<Card>* cur) {
    int count = 0;
    while (cur != nullptr) {
        count++;
        cur = cur->next;
    }
    return count;
}

// Constructor: start with an empty linked list
Deck::Deck() : head(nullptr) {}

// Destructor: automatically clears nodes when Deck is destroyed
Deck::~Deck() {
    clear(); // automatic cleanup to prevent memory leaks
}

bool Deck::empty() const {
    return head == nullptr;
}

int Deck::size() const {
    return listSize(head);
}

void Deck::clear() {
    deleteList(head);   // deletes all nodes
    head = nullptr;     // prevents dangling pointer
}

// Build a standard 52-card deck:
// suits: Clubs, Diamonds, Hearts, Spades
// ranks: 1..13 (A..K)
void Deck::buildStandard52() {
    clear(); // start fresh avoid accidentally appending another deck

    Card::Suit suits[] = {
        Card::Suit::Clubs,
        Card::Suit::Diamonds,
        Card::Suit::Hearts,
        Card::Suit::Spades
    };

    for (Card::Suit s : suits) {
        for (int r = 1; r <= 13; r++) {
            insertAtEnd(head, Card(r, s));
        }
    }
}

// Shuffle approach
void Deck::shuffle() {
    if (size() <= 1) 
        return; // nothing to shuffle for 0 or 1 card

    // Step 1: move cards to a vector
    std::vector<Card> temp;
    temp.reserve(size());
    while (!empty()) {
        temp.push_back(popFront(head)); // remove from top and store in vector
    }

    // Step 2: shuffle the vector
    std::random_device rd;
    std::mt19937 rng(rd());
    std::shuffle(temp.begin(), temp.end(), rng);

    // Step 3: rebuild the linked list
    for (const Card& c : temp) {
        insertAtEnd(head, c);
    }
}

Card Deck::dealOne() {
    return popFront(head);
}

// Cut the deck at k:
// Move the first k cards to the bottom.
// Example: [A B C D E], cut(2) -> [C D E A B]
void Deck::cut(int k) {
    int n = size();
    if (n <= 1) return;

    // normalize k to [0, n)
    k %= n;
    if (k < 0) k += n;
    if (k == 0) return;

    // Move k cards from top to bottom

    for (int i = 0; i < k; i++) {
        Card c = popFront(head);
        insertAtEnd(head, c);
    }
}

void Deck::printTopN(int n) const {
    const Node<Card>* cur = head;
    for (int i = 0; cur != nullptr && i < n; i++) {
        std::cout << cur->data;
        if (cur->next != nullptr && i < n - 1) std::cout << " ";
        cur = cur->next;
    }
    std::cout << std::endl;
}
