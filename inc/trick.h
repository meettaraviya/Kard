#pragma once
#include "card.h"
#include "constants.h"

template <uint8_t n>
struct Trick{
    Card* card_ptrs[n];
    Suit lead;
    uint8_t size = 0;
    Trick(Card*);
    void add(Card*);
    uint8_t winner();
};

template <uint8_t n>
std::ostream& operator<<(std::ostream& stream, Trick<n>& x);
