#pragma once

#include "Board.h"

class GameStateEvaluator
{
private:
    bool CheckVertical(int row, int col, Move p);
    bool CheckHorizontal(int row, int col, Move p);
    bool CheckDiagonal(int row, int col, Move p);
public:
    bool CheckWin(Board* state);
};