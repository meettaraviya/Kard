#pragma once
#include <cstdint>
#include <iostream>

enum Suit {DIAMONDS, CLUBS, HEARTS, SPADES};
enum Value {TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE};

extern Suit TRUMP;

struct Card{
    uint8_t id;
    Card();
    Card(uint8_t c);
    Card(Suit s, Value v);
    inline Suit suit() const;
    inline Value value() const;
    inline bool operator>(const Card&);
};

extern Card DECK[52];

std::ostream& operator<<(std::ostream& stream, const Card& x);