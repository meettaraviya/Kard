#pragma once
#include "common.h"
#include "utils.cpp"
#include "card.cpp"

Suit trump;

char* get_trump_name(){
    switch (trump)
    {
    case SPADES:
        return (char*) "Spades";
    case DIAMONDS:
        return (char*) "Diamonds";
    case CLUBS:
        return (char*) "Clubs";
    case HEARTS:
        return (char*) "Hearts";
    default:
        return (char*) "?";
    }
}

class Trick
{
public:
    vector<Card> cards;
    Trick(): cards() {}
    
    int winner(){
        int leadSuite = cards[0].suit;
        int best_i = 0;
        for(int i=1; i<cards.size(); i++){
            if(cards[i].suit == cards[best_i].suit){
                if(cards[i].value > cards[best_i].value){
                    best_i = i;
                }
            }
            else if(cards[i].suit == trump){
                best_i = i;
            }
        }
        return best_i;
    }
};
