#pragma once

#include "Board.h"
#include "Player.h"

class GameController
{
private:    
    Player* P1;
    Player* P2;

    int numMoves;
    int terminatingMoveCount;
    Board* BoardEntity;

    Move RunMove(bool p1);

    GameController();

public:
    GameController(Player* _p1, Player* _p2);

    Move PlayGame();
};