#include "gtest/gtest.h"
#include "Board.h"
#include "GameStateEvaluator.h"

#include <iostream>

#define DEBUG_PRINT false

TEST(GameStateEvaluatorTests, CountNFromLocationVerify)
{
	Board a = Board(6, 6, 4);
	GameStateEvaluator gse = GameStateEvaluator();

	int value = gse.CountNFromLocation(a.StateAccess(), 0, 0, P1_MOVE, 3);
}

TEST(GameStateEvaluatorTests, VerticalWins)
{
    Board a = Board(7, 6, 4);
    GameStateEvaluator gse = GameStateEvaluator();

    //Check that an empty board yiels no winner
    bool verticalResult = gse.CheckVertical(a.StateAccess(), 0, 0,
        P1_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(verticalResult, false);

    verticalResult = gse.CheckVertical(a.StateAccess(), 0, 0,
        P2_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(verticalResult, false);

    //Quirk of a test that double checks that if we call with player == EMPTY_MOVE, then expect a win always
    //  Consequence of implementation
    verticalResult = gse.CheckVertical(a.StateAccess(), 0, 0,
        NO_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(verticalResult, true);
    if (DEBUG_PRINT)
        cout << a.ToString();

    //Check that 1 move in a column is no win for either
    a = Board(7, 6, 4);
    a.MakeMove(1, P1_MOVE);
    verticalResult = gse.CheckVertical(a.StateAccess(), a.MoveRow, a.MoveCol,
        P1_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(verticalResult, false);
    verticalResult = gse.CheckVertical(a.StateAccess(), a.MoveRow, a.MoveCol,
        P2_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(verticalResult, false);
    if (DEBUG_PRINT)
        cout << a.ToString();

    //Check that a full column interleaved moves is no win for either
    a = Board(7, 6, 4);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(1, P2_MOVE);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(1, P2_MOVE);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(1, P2_MOVE);
    a.MakeMove(1, P1_MOVE);
    verticalResult = gse.CheckVertical(a.StateAccess(), a.MoveRow, a.MoveCol,
        P1_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(verticalResult, false);
    verticalResult = gse.CheckVertical(a.StateAccess(), a.MoveRow, a.MoveCol,
        P2_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(verticalResult, false);
    verticalResult = gse.CheckVertical(a.StateAccess(), a.MoveRow, a.MoveCol,
        NO_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(verticalResult, false);
    if (DEBUG_PRINT)
        cout << a.ToString();

    //Check that 4 in a row is win for one, but not for other
    a = Board(7, 6, 4);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(1, P1_MOVE);
    verticalResult = gse.CheckVertical(a.StateAccess(), a.MoveRow, a.MoveCol,
        P1_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(verticalResult, true);
    verticalResult = gse.CheckVertical(a.StateAccess(), a.MoveRow, a.MoveCol,
        P2_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(verticalResult, false);
    if (DEBUG_PRINT)
        cout << a.ToString();

    //Check that 3 in a row and 1 block is no win for either
    a = Board(7, 6, 4);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(1, P2_MOVE);
    verticalResult = gse.CheckVertical(a.StateAccess(), a.MoveRow, a.MoveCol,
        P1_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(verticalResult, false);
    verticalResult = gse.CheckVertical(a.StateAccess(), a.MoveRow, a.MoveCol,
        P2_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(verticalResult, false);
    if (DEBUG_PRINT)
        cout << a.ToString();

    //Check that 3 in a row and empty is no win for either
    a = Board(7, 6, 4);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(1, P1_MOVE);
    verticalResult = gse.CheckVertical(a.StateAccess(), a.MoveRow, a.MoveCol,
        P1_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(verticalResult, false);
    verticalResult = gse.CheckVertical(a.StateAccess(), a.MoveRow, a.MoveCol,
        P2_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(verticalResult, false);
    if (DEBUG_PRINT)
        cout << a.ToString();

    //Check that 4 in a row with form XXXOOOO is a win for O
    a = Board(7, 6, 4);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(1, P2_MOVE);
    a.MakeMove(1, P2_MOVE);
    a.MakeMove(1, P2_MOVE);
    a.MakeMove(1, P2_MOVE);
    verticalResult = gse.CheckVertical(a.StateAccess(), a.MoveRow, a.MoveCol,
        P1_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(verticalResult, false);
    verticalResult = gse.CheckVertical(a.StateAccess(), a.MoveRow, a.MoveCol,
        P2_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(verticalResult, true);
    if (DEBUG_PRINT)
        cout << a.ToString();

    //Check that 4 in a row with form OOOXXXX is a win for X
    a = Board(7, 6, 4);
    a.MakeMove(1, P2_MOVE);
    a.MakeMove(1, P2_MOVE);
    a.MakeMove(1, P2_MOVE);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(1, P1_MOVE);
    verticalResult = gse.CheckVertical(a.StateAccess(), a.MoveRow, a.MoveCol,
        P1_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(verticalResult, true);
    verticalResult = gse.CheckVertical(a.StateAccess(), a.MoveRow, a.MoveCol,
        P2_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(verticalResult, false);
    if (DEBUG_PRINT)
        cout << a.ToString();

    //Check that 4 in a row is win for none when ConnectLength=5
    a = Board(7, 6, 5);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(1, P1_MOVE);
    verticalResult = gse.CheckVertical(a.StateAccess(), a.MoveRow, a.MoveCol,
        P1_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(verticalResult, false);
    verticalResult = gse.CheckVertical(a.StateAccess(), a.MoveRow, a.MoveCol,
        P2_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(verticalResult, false);
    if (DEBUG_PRINT)
        cout << a.ToString();

    //Check that 5 in a row is win for P1 when ConnectLength=5
    a = Board(7, 6, 5);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(1, P1_MOVE);
    verticalResult = gse.CheckVertical(a.StateAccess(), a.MoveRow, a.MoveCol,
        P1_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(verticalResult, true);
    verticalResult = gse.CheckVertical(a.StateAccess(), a.MoveRow, a.MoveCol,
        P2_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(verticalResult, false);
    if (DEBUG_PRINT)
        cout << a.ToString();
}

TEST(GameStateEvaluatorTests, HorizontalWins)
{
    Board a;
    bool horizontalResult;
    GameStateEvaluator gse = GameStateEvaluator();
    
    //Check empty board is win for none
    a = Board(7, 6, 4);
    horizontalResult = gse.CheckHorizontal(a.StateAccess(), 0, 0,
        P1_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(horizontalResult, false);
    horizontalResult = gse.CheckHorizontal(a.StateAccess(), 0, 0,
        P2_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(horizontalResult, false);
    if (DEBUG_PRINT)
        cout << a.ToString();
    //Check X in col 0 position is win for none
    a = Board(7, 6, 4);
    a.MakeMove(1, P1_MOVE);
    horizontalResult = gse.CheckHorizontal(a.StateAccess(), a.MoveRow, a.MoveCol,
        P1_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(horizontalResult, false);
    horizontalResult = gse.CheckHorizontal(a.StateAccess(), a.MoveRow, a.MoveCol,
        P2_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(horizontalResult, false);
    if (DEBUG_PRINT)
        cout << a.ToString();
    //Check that 4 X in 0,1,2,3 is a win for X
    a = Board(7, 6, 4);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(2, P1_MOVE);
    a.MakeMove(3, P1_MOVE);
    a.MakeMove(4, P1_MOVE);
    horizontalResult = gse.CheckHorizontal(a.StateAccess(), a.MoveRow, a.MoveCol,
        P1_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(horizontalResult, true);
    horizontalResult = gse.CheckHorizontal(a.StateAccess(), a.MoveRow, a.MoveCol,
        P2_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(horizontalResult, false);
    if (DEBUG_PRINT)
        cout << a.ToString();
    //Expect XXXO is no win
    a = Board(7, 6, 4);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(2, P1_MOVE);
    a.MakeMove(3, P1_MOVE);
    a.MakeMove(4, P2_MOVE);
    horizontalResult = gse.CheckHorizontal(a.StateAccess(), a.MoveRow, a.MoveCol,
        P1_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(horizontalResult, false);
    horizontalResult = gse.CheckHorizontal(a.StateAccess(), a.MoveRow, a.MoveCol,
        P2_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(horizontalResult, false);
    if (DEBUG_PRINT)
        cout << a.ToString();
    //Expect XXXOX is no win
    a = Board(7, 6, 4);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(2, P1_MOVE);
    a.MakeMove(3, P1_MOVE);
    a.MakeMove(4, P2_MOVE);
    a.MakeMove(5, P1_MOVE);
    horizontalResult = gse.CheckHorizontal(a.StateAccess(), a.MoveRow, a.MoveCol,
        P1_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(horizontalResult, false);
    horizontalResult = gse.CheckHorizontal(a.StateAccess(), a.MoveRow, a.MoveCol,
        P2_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(horizontalResult, false);
    if (DEBUG_PRINT)
        cout << a.ToString();
    //Expect XXXXO is win
    a = Board(7, 6, 4);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(2, P1_MOVE);
    a.MakeMove(3, P1_MOVE);
    a.MakeMove(4, P1_MOVE);
    int moveR = a.MoveRow;
    int moveC = a.MoveCol;
    a.MakeMove(5, P2_MOVE);
    horizontalResult = gse.CheckHorizontal(a.StateAccess(), moveR, moveC,
        P1_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(horizontalResult, true);
    horizontalResult = gse.CheckHorizontal(a.StateAccess(), a.MoveRow, a.MoveCol,
        P2_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(horizontalResult, false);

}

TEST(GameStateEvaluatorTests, DiagonalWins)
{
    Board a;
    bool diagonalResult;
    GameStateEvaluator gse = GameStateEvaluator();

    //Check empty board is win for none
    a = Board(7, 6, 4);
    diagonalResult = gse.CheckDiagonal(a.StateAccess(), 0, 0,
        P1_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(diagonalResult, false);
    diagonalResult = gse.CheckDiagonal(a.StateAccess(), 0, 0,
        P2_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(diagonalResult, false);
    if (DEBUG_PRINT)
        cout << a.ToString();
    //Check diagonal up to left from origin in XXXX is win for P1
    a = Board(7, 6, 4);
    a.MakeMove(1, 4, P1_MOVE);
    a.MakeMove(2, 3, P1_MOVE);
    a.MakeMove(3, 2, P1_MOVE);
    a.MakeMove(4, 1, P1_MOVE);
    diagonalResult = gse.CheckDiagonal(a.StateAccess(), a.MoveRow, a.MoveCol,
        P1_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(diagonalResult, true);
    diagonalResult = gse.CheckDiagonal(a.StateAccess(), a.MoveRow, a.MoveCol,
        P2_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(diagonalResult, false);
    if (DEBUG_PRINT)
        cout << a.ToString();
    //Check diagonal up to left from origin in XXXO is no win
    a = Board(7, 6, 4);
    a.MakeMove(1, 4, P1_MOVE);
    a.MakeMove(2, 3, P1_MOVE);
    a.MakeMove(3, 2, P1_MOVE);
    a.MakeMove(4, 1, P2_MOVE);
    diagonalResult = gse.CheckDiagonal(a.StateAccess(), a.MoveRow, a.MoveCol,
        P1_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(diagonalResult, false);
    diagonalResult = gse.CheckDiagonal(a.StateAccess(), a.MoveRow, a.MoveCol,
        P2_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(diagonalResult, false);
    if (DEBUG_PRINT)
        cout << a.ToString();
    //Check diagonal down to right in XXXX is win for P1
    a = Board(7, 6, 4);
    a.MakeMove(4, 1, P1_MOVE);
    a.MakeMove(3, 2, P1_MOVE);
    a.MakeMove(2, 3, P1_MOVE);
    a.MakeMove(1, 4, P1_MOVE);
    diagonalResult = gse.CheckDiagonal(a.StateAccess(), a.MoveRow, a.MoveCol,
        P1_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(diagonalResult, true);
    diagonalResult = gse.CheckDiagonal(a.StateAccess(), a.MoveRow, a.MoveCol,
        P2_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(diagonalResult, false);
    if (DEBUG_PRINT)
        cout << a.ToString();
    //Check diagonal down to right in XXXO is no win
    a = Board(7, 6, 4);
    a.MakeMove(4, 1, P1_MOVE);
    a.MakeMove(3, 2, P1_MOVE);
    a.MakeMove(2, 3, P1_MOVE);
    a.MakeMove(1, 4, P2_MOVE);
    diagonalResult = gse.CheckDiagonal(a.StateAccess(), a.MoveRow, a.MoveCol,
        P1_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(diagonalResult, false);
    diagonalResult = gse.CheckDiagonal(a.StateAccess(), a.MoveRow, a.MoveCol,
        P2_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(diagonalResult, false);
    if (DEBUG_PRINT)
        cout << a.ToString();
    //Check diagonal up to right in XXXX is win for P1
    a = Board(7, 6, 4);
    a.MakeMove(1, 1, P1_MOVE);
    a.MakeMove(2, 2, P1_MOVE);
    a.MakeMove(3, 3, P1_MOVE);
    a.MakeMove(4, 4, P1_MOVE);
    diagonalResult = gse.CheckDiagonal(a.StateAccess(), a.MoveRow, a.MoveCol,
        P1_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(diagonalResult, true);
    diagonalResult = gse.CheckDiagonal(a.StateAccess(), a.MoveRow, a.MoveCol,
        P2_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(diagonalResult, false);
    if (DEBUG_PRINT)
        cout << a.ToString();
    //Check diagonal up to right in XXXO is no win
    a = Board(7, 6, 4);
    a.MakeMove(1, 1, P1_MOVE);
    a.MakeMove(2, 2, P1_MOVE);
    a.MakeMove(3, 3, P1_MOVE);
    a.MakeMove(4, 4, P2_MOVE);
    diagonalResult = gse.CheckDiagonal(a.StateAccess(), a.MoveRow, a.MoveCol,
        P1_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(diagonalResult, false);
    diagonalResult = gse.CheckDiagonal(a.StateAccess(), a.MoveRow, a.MoveCol,
        P2_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(diagonalResult, false);
    if (DEBUG_PRINT)
        cout << a.ToString();
    //Check diagonal down to left in XXXX is win for P1
    a = Board(7, 6, 4);
    a.MakeMove(4, 4, P1_MOVE);
    a.MakeMove(3, 3, P1_MOVE);
    a.MakeMove(2, 2, P1_MOVE);
    a.MakeMove(1, 1, P1_MOVE);
    diagonalResult = gse.CheckDiagonal(a.StateAccess(), a.MoveRow, a.MoveCol,
        P1_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(diagonalResult, true);
    diagonalResult = gse.CheckDiagonal(a.StateAccess(), a.MoveRow, a.MoveCol,
        P2_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(diagonalResult, false);
    if (DEBUG_PRINT)
        cout << a.ToString();
    //Check diagonal down to left in XXXO is No win
    a = Board(7, 6, 4);
    a.MakeMove(4, 4, P1_MOVE);
    a.MakeMove(3, 3, P1_MOVE);
    a.MakeMove(2, 2, P1_MOVE);
    a.MakeMove(1, 1, P2_MOVE);
    diagonalResult = gse.CheckDiagonal(a.StateAccess(), a.MoveRow, a.MoveCol,
        P1_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(diagonalResult, false);
    diagonalResult = gse.CheckDiagonal(a.StateAccess(), a.MoveRow, a.MoveCol,
        P2_MOVE, a.ConnectLength, a.NumRow, a.NumCol);
    EXPECT_EQ(diagonalResult, false);

}

TEST(GameStateEvaluatorTests, GeneralWinsP1)
{
    Board a;
    bool generalResult;
    GameStateEvaluator gse = GameStateEvaluator();

    //Check typical game 
    a = Board(7, 6, 4);
    a.MakeMove(1, P2_MOVE);
    a.MakeMove(3, P1_MOVE);
    a.MakeMove(2, P2_MOVE);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(3, P2_MOVE);
    a.MakeMove(3, P1_MOVE);
    a.MakeMove(5, P2_MOVE);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(5, P2_MOVE);
    a.MakeMove(3, P1_MOVE);
    a.MakeMove(1, P2_MOVE);
    a.MakeMove(3, P1_MOVE);
    a.MakeMove(4, P2_MOVE);
    a.MakeMove(5, P1_MOVE);
    a.MakeMove(1, P2_MOVE);
    a.MakeMove(6, P1_MOVE);
    a.MakeMove(1, P2_MOVE);
    a.MakeMove(3, P1_MOVE);
    generalResult = gse.CheckWin(&a, P1_MOVE);
    EXPECT_EQ(generalResult, true);
    generalResult = gse.CheckWin(&a, P2_MOVE);
    EXPECT_EQ(generalResult, false);
    if (DEBUG_PRINT)
        cout << a.ToString();
}

TEST(GameStateEvaluatorTests, GeneralWinsP2)
{
    Board a;
    bool generalResult;
    GameStateEvaluator gse = GameStateEvaluator();

    //Check typical game 
    a = Board(7, 6, 4);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(3, P2_MOVE);
    a.MakeMove(2, P1_MOVE);
    a.MakeMove(1, P2_MOVE);
    a.MakeMove(3, P1_MOVE);
    a.MakeMove(3, P2_MOVE);
    a.MakeMove(5, P1_MOVE);
    a.MakeMove(1, P2_MOVE);
    a.MakeMove(5, P1_MOVE);
    a.MakeMove(3, P2_MOVE);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(3, P2_MOVE);
    a.MakeMove(4, P1_MOVE);
    a.MakeMove(5, P2_MOVE);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(6, P2_MOVE);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(3, P2_MOVE);
    generalResult = gse.CheckWin(&a, P1_MOVE);
    EXPECT_EQ(generalResult, false);
    generalResult = gse.CheckWin(&a, P2_MOVE);
    EXPECT_EQ(generalResult, true);
    if (DEBUG_PRINT)
        cout << a.ToString();
}
