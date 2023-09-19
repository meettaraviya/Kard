#include "card.h"

Suit TRUMP = Suit::SPADES;

Card::Card(){}

Card::Card(uint8_t c): id(c) {}

Card::Card(Suit s, Value v): id(s*NV+v) {}

inline Suit Card::suit() const {return (Suit) (id/NV);}

inline Value Card::value() const {return (Value) (id%NV);}

bool Card::operator>(const Card& x) {return (suit()==x.suit())?(value()>x.value()):(suit()==TRUMP);}

Card DECK[DS] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51};

inline std::ostream& operator<<(std::ostream& stream, const Suit x){
    switch(x){
        case Suit::DIAMONDS: stream << RED << "♦"; break;
        case Suit::CLUBS: stream << BLUE << "♣"; break;
        case Suit::HEARTS: stream << RED << "♥"; break;
        case Suit::SPADES: stream << BLUE << "♠"; break;
    }
}

inline std::ostream& operator<<(std::ostream& stream, const Value x){
    switch(x){
        case Value::JACK: stream << "J"; break;
        case Value::QUEEN: stream << "Q"; break;
        case Value::KING: stream << "K"; break;
        case Value::ACE: stream << "A"; break;
        case Value::TEN: stream << "T"; break;
        default: stream << 2 + x - Value::TWO;
    }
}

std::ostream& operator<<(std::ostream& stream, const Card& x){
    stream << x.suit() << x.value();
    return stream;
}