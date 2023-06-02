#pragma once
#include "card.h"

template <uint8_t n>
struct Trick{
    Card cards[n];
    Suit lead;
    uint8_t size = 0;
    Trick(Card);
    void add(Card);
    uint8_t winner();
};