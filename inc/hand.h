#pragma once
#include <iterator>
#include "card.h"
#include "constants.h"

template <uint8_t n>
struct Hand{
    Card cards[n];
    uint8_t size = n;

    // Hand(Card[n]);
    Hand();

    void remove(Card&);

    struct Iterator
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = Card;
        using pointer           = value_type*;
        using reference         = value_type&;

        Iterator(pointer);
        reference operator*() const;
        pointer operator->();
        Iterator& operator++();
        Iterator operator++(int);
        bool operator== (const Iterator&) const;
        bool operator!= (const Iterator&) const;

    private:
        pointer m_ptr;
    };

    Iterator begin();
    Iterator end();

};

template <uint8_t n>
std::ostream& operator<<(std::ostream& stream, Hand<n>& x);
