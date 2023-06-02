#include "trick.h"

template <uint8_t n>
Trick<n>::Trick(Card c): lead(c.suit()) {cards[size++] = c;}

template <uint8_t n>
void Trick<n>::add(Card c) {cards[size++] = c;}

template <uint8_t n>
uint8_t Trick<n>::winner(){
    uint8_t i = 0;
    for(int j=0; j<n; j++) i = (cards[j]>cards[i])?j:i;
    return i;
}