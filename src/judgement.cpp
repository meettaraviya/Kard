#include <algorithm>
#include <cstring>
#include "hand.h"
#include "card.h"
#include "constants.h"
#include "fann.h"
#include "trick.h"

#define BPCS 100
#define BPIS (DS+2)
#define CPCS 1300
#define CPIS (DS+DS+DS+NS+n+NS*n+n+1)

using namespace std;

template struct Trick<NT>;

template <uint8_t n, uint8_t m>
struct Judgement{

    Hand<m> hands[n];
    uint8_t bets[n], counts[n];

    struct BetPlacer {
        fann* ann;
        fann_type inp[BPCS][n][BPIS] = {0.}, out[BPCS][n] = {0.};
        static uint16_t ci;
        
        BetPlacer(){
            const uint32_t sizes[] = {BPIS, 64, 16, 4, 1};
            ann = fann_create_standard_array(sizeof(sizes)/sizeof(sizes[0]), sizes);
            fann_set_activation_function_hidden(ann, FANN_ELLIOT_SYMMETRIC);
            fann_set_activation_function_output(ann, FANN_LINEAR);
            memset(inp, 0., sizeof inp);
        }

        void place_bets(Hand<m> hands[n], uint8_t bets[n]){
            uint8_t left = m;
            for(uint8_t i=0; i<n; i++){
                for(Card card: hands[i]){
                    inp[ci][i][card.id] = 1.;
                }
                inp[ci][i][DS] = n - i;
                inp[ci][i][DS+1] = left / inp[ci][i][DS];

                out[ci][i] = *fann_run(ann, inp[ci][i]);
                bets[i] = (out[ci][i] < 0) ? (0) : ((out[ci][i]>m)?m:((uint8_t) out[ci][i]));
                left -= bets[i];
            }
            ci=(ci+1)%BPCS;
        }

        void set_targets(uint8_t counts[n]){
            ci = (ci+BPCS-1)%BPCS;
            for(uint8_t i=0; i<n; i++) out[ci][i] = counts[i];
            ci = (ci+1)%BPCS;
        }
    };

    struct CardPlayer {
        fann* ann;
        fann_type inp[CPCS][n][CPIS] = {0.}, out[CPCS][n][DS] = {0.};
        static uint16_t ci;
        fann_type loc[DS], cutting_suits[n][NS];
        
        CardPlayer(){
            const uint32_t sizes[] = {CPIS, 256, 128, 64, DS};
            ann = fann_create_standard_array(sizeof(sizes)/sizeof(sizes[0]), sizes);
            fann_set_activation_function_hidden(ann, FANN_ELLIOT_SYMMETRIC);
            fann_set_activation_function_output(ann, FANN_SIGMOID_SYMMETRIC);
            memset(inp, 0., sizeof inp);
            memset(loc, 0., sizeof loc);
            memset(cutting_suits, 0., sizeof cutting_suits);
        }

        Trick<n>& play_trick(Hand<m> hands[n], uint8_t bets[n], uint8_t counts[n], uint8_t lead, uint8_t id){
            uint8_t left = m;
            Trick<n>* t = NULL;
            for(uint8_t _i=0; _i<n; _i++){
                uint8_t i = (lead + _i) % n;
                for(Card card: hands[i]){
                    inp[ci][i][card.id] = 1.;
                }
                memcpy(loc, &inp[ci][DS], sizeof loc);
                if(t!=NULL){
                    for(uint8_t j=0; j<(t->size); j++){
                        inp[ci][i][2*DS+(t->card_ptrs[j]->id)] = 1.;
                    }
                    inp[ci][i][3*DS+(t->lead)] = 1.;
                    inp[ci][i][3*DS+NS+(t->winner())] = 1.;
                }
                memcpy(cutting_suits, &inp[ci][i][3*DS+NS+n], sizeof cutting_suits);
                for(uint8_t j=0; j<n; j++){
                    inp[ci][i][DS+DS+DS+NS+n+NS*n+j] = (bets[j]-counts[j])/(n-i);
                }
                inp[ci][i][DS+DS+DS+NS+n+NS*n+n] = n - i;

                bool cutting = true;
                if(t!=NULL and !cutting_suits[i][t->lead]){
                    for(Card c: hands[i]) if(c.suit()==(t->lead)) cutting = false;
                    cutting_suits[i][t->lead] = (fann_type) cutting;
                }

                memcpy(fann_run(ann, inp[ci][i]), &out[ci][i], DS*(sizeof (fann_type)));
                uint8_t k = 0;
                if(!cutting) while(hands[i].cards[k].suit()!=t->lead) k++;
                for(uint8_t j = k+1; j<hands[i].size; j++)
                if(out[ci][i][hands[i].cards[j].id] > out[ci][i][hands[i].cards[k].id] and (cutting or hands[i].cards[j].suit()==t->lead)) k = j;
                if(!cutting) for(uint8_t j = 0; j<hands[i].size; j++) if(hands[i].cards[j].suit()==t->lead) out[ci][i][hands[i].cards[j].id] = -1.;
                if(t==NULL){
                    hands[i].remove(k);
                    t = new Trick<n>(&hands[i].cards[hands[i].size]);
                }
                else{
                    hands[i].remove(k);
                    t->add(&hands[i].cards[hands[i].size]);
                }
            }
            ci = (ci+1)%CPCS;
            return *t;
        }

        void set_targets(fann_type r){
            ci = (ci+CPCS-1)%CPCS;
            for(uint8_t i=0; i<n; i++) out[ci][i] = counts[i];
            ci = (ci+1)%CPCS;
        }
    };

    uint8_t lead;

    BetPlacer bp;
    CardPlayer cp;
    Judgement(){
        random_shuffle(DECK, DECK+DS);
        bp.ci = 0;
        for(uint8_t i=0; i<n; i++) {
            copy(DECK+m*i, DECK+m*(i+1), hands[i].begin());
            hands[i].size = m;
            bets[i] = 0;
            cout << hands[i];
        }
        bp.place_bets(hands, bets);
        for(uint8_t i=0; i<n; i++){
            cout << BOLD << i + 1 << RESET << " bets " << (int) bets[i] << endl;
        }
        lead = 0;
        for(uint8_t i=0; i<m; i++){
            Trick<n> t = cp.play_trick(hands, bets, counts, lead, i);
            counts[t.winner()]++;
            cout << "Leader: " << BOLD << (int) lead << RESET << " | ";
            for(uint8_t j=0; j<n; j++)
            cout << (j==lead? UNDERLINED : "") << (j==t.winner()?BOLD:"") << *t.card_ptrs[(j+n-lead)%n] << RESET << " ";
            lead = (lead+t.winner())%n;
            cout << "| Winner: " << BOLD << (int) lead << RESET << " | Tricks: ";
            for(uint8_t j=0; j<n; j++)
            cout << (counts[j]==bets[j]? GREEN : "") << (j==t.winner()?BOLD:"") << (int) counts[j] << "/" << (int) bets[j] << RESET << " ";
            cout << endl;
        }
    }
};

template <uint8_t n, uint8_t m>
uint16_t Judgement<n, m>::BetPlacer::ci = 0;

template <uint8_t n, uint8_t m>
uint16_t Judgement<n, m>::CardPlayer::ci = 0;

int main(){
    Judgement<NP, NT> game;   
    return 0;
}
