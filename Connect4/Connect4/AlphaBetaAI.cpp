#include "AlphaBetaAI.h"

AlphaBetaAI::AlphaBetaAI() {}

int AlphaBetaAI::DepthNormalise(int value)
{
    return 0;
}

AlphaBetaAI::AlphaBetaAI(Move _p)
{
    player = _p;
}

int AlphaBetaAI::GetBestMove()
{
    return 0;
}

void AlphaBetaAI::Play(Board * _CurrentBoard)
{
    CurrentBoard = new Board(*_CurrentBoard);



}
