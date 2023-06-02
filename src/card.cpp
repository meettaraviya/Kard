#include "card.h"

Suit TRUMP = Suit::SPADES;

Card::Card(){}

Card::Card(uint8_t c): id(c) {}

Card::Card(Suit s, Value v): id(s*13+v) {}

inline Suit Card::suit() const {return (Suit) (id/13);}

inline Value Card::value() const {return (Value) (id%13);}

inline bool Card::operator>(const Card& x) {return (suit()==x.suit())?(value()>x.value()):(suit()==TRUMP);}

Card DECK[52] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51};

std::ostream& operator<<(std::ostream& stream, const Card& x){
    switch(x.suit()){
        case Suit::DIAMONDS: stream << "♦"; break;
        case Suit::CLUBS: stream << "♣"; break;
        case Suit::HEARTS: stream << "♥"; break;
        case Suit::SPADES: stream << "♠"; break;
    }
    switch(x.value()){
        case Value::JACK: stream << "J"; break;
        case Value::QUEEN: stream << "Q"; break;
        case Value::KING: stream << "K"; break;
        case Value::ACE: stream << "A"; break;
        default: stream << 2 + x.value() - Value::TWO;
    }
    return stream;
}