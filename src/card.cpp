#pragma once
#include "common.h"
#include <algorithm>

enum Suit {JOKERY, HEARTS, SPADES, DIAMONDS, CLUBS};
enum Value {
    ACE = 14,
    ONE = 1,
    TWO = 2,
    THREE = 3,
    FOUR = 4,
    FIVE = 5,
    SIX = 6,
    SEVEN = 7,
    EIGHT = 8,
    NINE = 9,
    TEN = 10,
    JACK = 11,
    QUEEN = 12,
    KING = 13,
    JOKER = 0
};

class Card
{
public:
    Suit suit;
    Value value;
    Card(Suit s, Value v): suit(s), value(v) {

    }

    static vector<Card> get_deck(bool use_ones=false, bool joker_count=0, bool shuffle=true){
        vector<Card> deck;
        for(int i=2; i<=10; i++){
            deck.push_back(Card(HEARTS, (Value) i));
            deck.push_back(Card(SPADES, (Value) i));
            deck.push_back(Card(DIAMONDS, (Value) i));
            deck.push_back(Card(CLUBS, (Value) i));
        }
        if(use_ones){
            deck.push_back(Card(HEARTS, ONE));
            deck.push_back(Card(SPADES, ONE));
            deck.push_back(Card(DIAMONDS, ONE));
            deck.push_back(Card(CLUBS, ONE));
        }
        else{
            deck.push_back(Card(HEARTS, ACE));
            deck.push_back(Card(SPADES, ACE));
            deck.push_back(Card(DIAMONDS, ACE));
            deck.push_back(Card(CLUBS, ACE));
        }
        for(int i=0; i<joker_count; i++){
            deck.push_back(Card(Suit::JOKERY, Value::JOKER));
        }
        if(shuffle){
            random_shuffle(deck.begin(), deck.end());
        }
        return deck;
    }

    bool operator==(const Card &other){
        return (other.suit == suit) and (other.value == value);
    }
};
