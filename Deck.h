#ifndef DECK_H
#define DECK_H

#include "Card.h"

// Forward declare the template Node (so Deck.h doesn't need node.h)
template <typename T>
class Node;

class Deck {
private:
    Node<Card>* head;  // pointer is OK with forward declaration

public:
    Deck();
    ~Deck();

    bool empty() const;
    int size() const;

    void clear();
    void buildStandard52();
    void shuffle();
    Card dealOne();
    void cut(int k);
    void printTopN(int n) const;
};

#endif //DECK_H
