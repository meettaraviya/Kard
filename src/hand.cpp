#include "hand.h"

template <uint8_t n>
void Hand<n>::remove(Card& x){std::swap(x, cards[--size]);}

// template <uint8_t n>
// Hand<n>::Hand(Card cs[n]): size(n) {cards = (Card[n]) cs;}

template <uint8_t n>
Hand<n>::Hand(): size(0) {}

template <uint8_t n>
Hand<n>::Iterator::Iterator(pointer ptr): m_ptr(ptr) {};
template <uint8_t n>
Hand<n>::Iterator::reference Hand<n>::Iterator::operator*() const {return *m_ptr;}
template <uint8_t n>
Hand<n>::Iterator::pointer Hand<n>::Iterator::operator->() {return m_ptr;}
template <uint8_t n>
Hand<n>::Iterator& Hand<n>::Iterator::operator++() {m_ptr++; return *this;}
template <uint8_t n>
Hand<n>::Iterator Hand<n>::Iterator::operator++(int) {Iterator tmp = *this; ++(*this); return tmp;}
template <uint8_t n>
bool Hand<n>::Iterator::operator== (const Iterator& b) const {return m_ptr == b.m_ptr;};
template <uint8_t n>
bool Hand<n>::Iterator::operator!= (const Iterator& b) const {return m_ptr != b.m_ptr;};
template <uint8_t n>
Hand<n>::Iterator Hand<n>::begin() {return Hand<n>::Iterator(&cards[0]);}
template <uint8_t n>
Hand<n>::Iterator Hand<n>::end() {return Hand<n>::Iterator(&cards[size]);}

template <uint8_t n>
std::ostream& operator<<(std::ostream& stream, Hand<n>& x){
    for(auto card: x) std::cout << card << ' '; std::cout << std::endl;
    return stream;
}

template std::ostream& operator<<(std::ostream& stream, Hand<T>& x);
template struct Hand<T>;
