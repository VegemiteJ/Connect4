#pragma once

#include "Player.h"
#include "AlphaBetaAI.h"

class IterativeDeepenAI : public Player
{
public:
	int BestUtility;

	IterativeDeepenAI(Move _p);
	IterativeDeepenAI(Move _p, int _startDepth);

	void Play(Board* _CurrentBoard);
	int GetBestMove();
private:
    AlphaBetaAI ai;

    Move p;
    int startDepth;
    //int BestMove; - Inherited from player

    double ExpectedTime(int numCols, int depth);
};