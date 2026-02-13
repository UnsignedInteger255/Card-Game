// Enumerated Rank and Suit
enum Rank {Ace, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King};
// Odd numbers (1,3) are black suits (Spade, Club) 
// Even numbers (2,4) are red suits (Heart, Diamond)
enum Suit {Spade, Heart, Club, Diamond};

// Create card class with two members
class Card {
    public:
        Rank rank;
        Suit suit;
    
        Card(Rank r, Suit s) {
            this->rank = r;
            this->suit = s;
        }
};
