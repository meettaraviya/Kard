// #define DEBUG
#pragma once
#include "common.h"
#include "game.cpp"
#include "trick.cpp"

using namespace std;

void initialize(){
   trump = Suit::JOKERY;
   srand(time(NULL));
}

int main()
{
   initialize();
   vector<int> score(4);
   for(int i=0; i<10000; i++){
      Game game;
      game.play();
   for(int i=0; i<4; i++){
      score[i] += game.players[i].score;
      printf("%.2f ", ((float) score[i]) / 100);
   } printf("\n");
   }
}