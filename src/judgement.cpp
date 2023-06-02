#include <algorithm>
#include "hand.h"
#include "card.h"
#include "constants.h"

using namespace std;

template <uint8_t n, uint8_t m>
struct Judgement{
    struct Player {
        Hand<m> hand;
        uint8_t bet;
        Player(){}
    };
    Player players[n];
    Judgement(){
        random_shuffle(DECK, DECK+52);
        for(int i=0; i<n; i++) {
            copy(DECK+m*i, DECK+m*(i+1), players[i].hand.begin());
            players[i].hand.size = m;
            cout << players[i].hand;
        }
    }
};

int main(){
    Judgement<N, T> game;   
    return 0;
}
