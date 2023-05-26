#pragma once
#include "common.h"
#include "card.cpp"
#include "trick.cpp"

class Game;

class Player
{
public:
    int score = 0;
    int prediction = 0;
    int tricks = 0;
    int index = -1;
    vector<Card> hand;
    Game* game;
    Player(Game* g, int i): game(g), index(i) {}
    int get_prediction(vector<int> predictions){
        return 3;
    }
    Card get_play(Trick trick){
        if(trick.cards.size() == 0){
            return hand[0];
        }
        else{
            Suit leadSuit = trick.cards[0].suit;
            for(auto card: hand){
                if(card.suit == leadSuit){
                    return card;
                }
            }
            return hand[0];
        }
    }
};
