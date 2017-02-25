#pragma once

#include "Player.h"
#include "Board.h"

class AlphaBetaAI : public Player
{
private:
    AlphaBetaAI();

    Move player;
    Board* CurrentBoard;
    int BestUtility;

    //Scale the absolute value of value upwards
    //	Returns modified value
    //	e.g. Value 950 becomes 951, -950 becomes -951
    int DepthNormalise(int value);

public:
    AlphaBetaAI(Move _p);

    int GetBestMove();
    void Play(Board* _CurrentBoard);
};