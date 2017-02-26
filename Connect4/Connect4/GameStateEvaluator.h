#pragma once

#include "Board.h"

class GameStateEvaluator
{
private:
    #pragma region GoogleTests
    #include "gtest/gtest_prod.h"
    FRIEND_TEST(GameStateEvaluatorTests, VerticalWins);
    FRIEND_TEST(GameStateEvaluatorTests, HorizontalWins);
    FRIEND_TEST(GameStateEvaluatorTests, DiagonalWins);
    #pragma endregion

    bool CheckVertical(Matrix* state, int row, int col, Move p, int ConnectLength, int NumRow, int NumCol);
    bool CheckHorizontal(Matrix* state, int row, int col, Move p, int ConnectLength, int NumRow, int NumCol);
    bool CheckDiagonal(Matrix* state, int row, int col, Move p, int ConnectLength, int NumRow, int NumCol);
    bool CheckPosition(Matrix* state, int row, int col, Move p, int NumRow, int NumCol);
public:
    bool CheckWin(Board* state, Move p);

    int ComputeUtility(Board* evaluationPosition, int _depth);

    int ComputeWinUtility(Board* evaluationPosition, Move p, Move player);
};