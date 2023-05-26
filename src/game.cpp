#pragma once
#include "common.h"
#include "card.cpp"
#include "trick.cpp"
#include "player.cpp"

class Game{
public:
    int numPlayers, numRounds, cardCount, leader;
    vector<Player> players;

    int roundId = 0;
    Suit trumpOrder[4] = {SPADES, DIAMONDS, CLUBS, HEARTS};
    Game(int n=4, int m=12):
        numPlayers(n),
        numRounds(m),
        cardCount(52 / n),
        leader(0)
        {
            for(int i=0; i<n; i++) players.push_back(Player(this, i));
        }

    void play(){
        for(roundId=0; roundId<numRounds; roundId++){
            play_round();
        }
    }

    void play_round(){
        trump = trumpOrder[roundId % 4];
        leader = roundId%numPlayers;
        #ifdef DEBUG
        printf("Starting Round %d with trump=%s. Player %d starts.\n", roundId+1, get_trump_name(), leader+1);
        #endif
        vector<Card> deck = Card::get_deck();
        vector<int> predictions;
        for(int i=0; i<numPlayers; i++){
            players[i].hand = vector<Card>(deck.begin()+i*cardCount, deck.begin()+(i+1)*cardCount);
            players[i].tricks = 0;
            players[i].prediction = players[i].get_prediction(predictions);
            predictions.push_back(players[i].prediction);
        }
        int trickLeader = leader;
        for(int i=0; i<cardCount; i++){
            trickLeader = resolve_trick(trickLeader);
        }
        score_round();
        #ifdef DEBUG
        for(int i=0; i<numPlayers; i++){
            printf("Score for Player %d: %3d\n", i+1, players[i].score);
        }
        printf("Round %d complete\n", roundId+1);
        #endif
    }

    int resolve_trick(int trickLeader){
        Trick trick;
        for(int i_=0; i_<numPlayers; i_++){
            int i = (i_+trickLeader)%numPlayers;
            Card play = players[i].get_play(trick);
            trick.cards.push_back(play);
            players[i].hand.erase(find(players[i].hand.begin(), players[i].hand.end(), play));
        }
        int winner = trick.winner();
        players[winner].tricks++;
        return winner;
    }

    void score_round(){
        for(int i=0; i<numPlayers; i++){
            if(players[i].tricks == players[i].prediction){
                players[i].score += (cardCount - cardCount/numPlayers + players[i].prediction);
                players[i].tricks = 0;
                players[i].prediction = 0;
                players[i].hand.clear();
            }
        }
    }
};
