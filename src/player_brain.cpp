#pragma once
#include "common.h"
#include "player.cpp"
#include "game.cpp"

class PlayerBrain
{
public:
    Game* game;
    Player* player;
    PlayerBrain(Game* g, Player* p): game(g), player(p) {}
};
