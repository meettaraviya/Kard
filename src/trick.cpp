#include "trick.h"

template <uint8_t n>
Trick<n>::Trick(Card* c): lead(c->suit()) {card_ptrs[size++] = c;}

template <uint8_t n>
void Trick<n>::add(Card* c) {card_ptrs[size++] = c;}

template <uint8_t n>
uint8_t Trick<n>::winner(){
    uint8_t i = 0;
    for(uint8_t j=0; j<size; j++) i = (card_ptrs[j]->id)>(card_ptrs[i]->id) ? j : i;
    return i;
}

template <uint8_t n>
std::ostream& operator<<(std::ostream& stream, Trick<n>& x){
    bool z = (x.lead == x.card_ptrs[0]->suit());

    stream << BOLD << x.lead << RESET << " lead: " << RESET;
    for(uint8_t i=0; i<x.size; i++) stream << *x.card_ptrs[i] << " ";
    // stream << RESET; stream << "| Winner: " << BOLD << (int) x.winner() << RESET;
    stream << RESET;
    return stream;
}

template std::ostream& operator<<(std::ostream& stream, Trick<NP>& x);
template struct Trick<NP>;