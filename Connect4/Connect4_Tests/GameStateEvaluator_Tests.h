#include "gtest/gtest.h"
#include "Board.h"
#include "GameStateEvaluator.h"

#include <iostream>

#define DEBUG_PRINT false

TEST(GameStateEvaluatorPublicTest, Connect3Public)
{
	Board a = Board(6, 6, 4);
	GameStateEvaluator gse = GameStateEvaluator();
	int value;

	//First test that 3 in middle yields 2
	a.MakeMove(2, P1_MOVE);
	a.MakeMove(3, P1_MOVE);
	a.MakeMove(4, P1_MOVE);
	value = gse.ComputeThreeInRow(&a);
	EXPECT_EQ(value, 2);

	//Check opponent has value 2
	value = gse.ComputeThreeInRow(&a);
	EXPECT_EQ(value, 2);

	//Check P2 has 1 possible and P1 has two - expects P2 to have 1 utility, P1 to have -1
	a = Board(6, 6, 4);
	a.MakeMove(1, P2_MOVE);
	a.MakeMove(2, P2_MOVE);
	a.MakeMove(3, P2_MOVE);
	a.MakeMove(1, P1_MOVE);
	a.MakeMove(2, P1_MOVE);
	a.MakeMove(3, P1_MOVE);
	a.MakeMove(1, P1_MOVE);
	a.MakeMove(2, P1_MOVE);
	a.MakeMove(3, P1_MOVE);
	value = gse.ComputeThreeInRow(&a);
	EXPECT_EQ(value, 1);

	//Now block P2 and check that P1 now has 3 possible
	a.MakeMove(4, P1_MOVE);
	value = gse.ComputeThreeInRow(&a);
	EXPECT_EQ(value, 3);

	//Check when both have 1 possible, net is 0
	a = Board(6, 6, 4);
	a.MakeMove(1, P1_MOVE);
	a.MakeMove(1, P1_MOVE);
	a.MakeMove(1, P1_MOVE);

	a.MakeMove(2, P2_MOVE);
	a.MakeMove(2, P2_MOVE);
	a.MakeMove(2, P2_MOVE);
	value = gse.ComputeThreeInRow(&a);
	EXPECT_EQ(value, 0);
}

TEST(GameStateEvaluatorTests, CountNTotal)
{
	Board a = Board(6, 6, 4);
	GameStateEvaluator gse = GameStateEvaluator();
	int value;

	//Try entire bottom left filled, leaving one space -> expects 1
	a.MakeMove(1, P2_MOVE);
	a.MakeMove(2, P2_MOVE);
	a.MakeMove(3, P2_MOVE);
	value = gse.CountN(a.StateAccess(), P2_MOVE, 3);
	EXPECT_EQ(value, 1);
	value = gse.CountN(a.StateAccess(), P1_MOVE, 3);
	EXPECT_EQ(value, 0);
	value = gse.CountN(a.StateAccess(), P2_MOVE, 2);
	EXPECT_EQ(value, 1);
	value = gse.CountN(a.StateAccess(), P2_MOVE, 1);
	EXPECT_EQ(value, 9);

	//Try middle, leaving gap on either end
	a = Board(6, 6, 4);
	a.MakeMove(2, P1_MOVE);
	a.MakeMove(3, P1_MOVE);
	a.MakeMove(4, P1_MOVE);
	value = gse.CountN(a.StateAccess(), P1_MOVE, 3);
	EXPECT_EQ(value, 2);
	//	Now modify board to block off one end with opponents move
	a.MakeMove(5, P2_MOVE);
	value = gse.CountN(a.StateAccess(), P1_MOVE, 3);
	EXPECT_EQ(value, 1);
	//	Now fully block off all possible c3 moves
	a.MakeMove(1, P2_MOVE);
	value = gse.CountN(a.StateAccess(), P1_MOVE, 3);
	EXPECT_EQ(value, 0);
}

TEST(GameStateEvaluatorTests, CountNFromLocationVerify)
{
	Board a = Board(6, 6, 4);
	GameStateEvaluator gse = GameStateEvaluator();
	//Empty Board test
	int value = gse.CountNFromLocation(a.StateAccess(), 0, 0, P1_MOVE, 3);
	if (DEBUG_PRINT) {
		cout << "Board: \t" << a.ToString() << endl;
	}
	EXPECT_EQ(value, 0);
	
	//One valid 3 in row test: bottom left to centre
	a.MakeMove(1, P1_MOVE);
	value = gse.CountNFromLocation(a.StateAccess(), 5, 0, P1_MOVE, 3);
	EXPECT_EQ(value, 0);

	a.MakeMove(2, P1_MOVE);
	value = gse.CountNFromLocation(a.StateAccess(), 5, 0, P1_MOVE, 3);
	EXPECT_EQ(value, 0);
	
	a.MakeMove(3, P1_MOVE);
	if (DEBUG_PRINT) {
		cout << "Board: \t" << a.ToString() << endl;
	}
	value = gse.CountNFromLocation(a.StateAccess(), 4, 0, P1_MOVE, 3);
	EXPECT_EQ(value, 0);
	value = gse.CountNFromLocation(a.StateAccess(), 4, 1, P1_MOVE, 3);
	EXPECT_EQ(value, 0);
	value = gse.CountNFromLocation(a.StateAccess(), 4, 2, P1_MOVE, 3);
	EXPECT_EQ(value, 0);
	value = gse.CountNFromLocation(a.StateAccess(), 4, 3, P1_MOVE, 3);
	EXPECT_EQ(value, 0);
	value = gse.CountNFromLocation(a.StateAccess(), 5, 3, P1_MOVE, 3);
	EXPECT_EQ(value, 1);

	//Testing differnt connect length + more than one connection from a single point
	Board b = Board(6, 6, 4);
	b.MakeMove(1, P1_MOVE);
	b.MakeMove(2, P1_MOVE);
	b.MakeMove(4, P1_MOVE);
	b.MakeMove(5, P1_MOVE);
	value = gse.CountNFromLocation(b.StateAccess(), 5, 2, P1_MOVE, 3);
	EXPECT_EQ(value, 0);
	value = gse.CountNFromLocation(b.StateAccess(), 5, 2, P1_MOVE, 2);
	EXPECT_EQ(value, 2);

	//Test vertical connect length
	b = Board(6, 6, 4);
	b.MakeMove(1, P1_MOVE);
	b.MakeMove(1, P1_MOVE);
	b.MakeMove(1, P1_MOVE);
	value = gse.CountNFromLocation(b.StateAccess(), 2, 0, P1_MOVE, 3);
	EXPECT_EQ(value, 1);
	value = gse.CountNFromLocation(b.StateAccess(), 2, 1, P1_MOVE, 3);
	EXPECT_EQ(value, 0);
	value = gse.CountNFromLocation(b.StateAccess(), 3, 1, P1_MOVE, 3);
	EXPECT_EQ(value, 0);
	value = gse.CountNFromLocation(b.StateAccess(), 4, 1, P1_MOVE, 3);
	EXPECT_EQ(value, 0);
	value = gse.CountNFromLocation(b.StateAccess(), 5, 1, P1_MOVE, 3);
	EXPECT_EQ(value, 0);

	//Test diagonal connect length
	//	Down to left
	b = Board(6, 6, 4);
	b.MakeMove(2, P1_MOVE);
	b.MakeMove(2, P1_MOVE);
	b.MakeMove(3, P2_MOVE);
	b.MakeMove(3, P2_MOVE);
	b.MakeMove(3, P1_MOVE);
	b.MakeMove(4, P2_MOVE);
	b.MakeMove(4, P2_MOVE);
	b.MakeMove(4, P2_MOVE);
	b.MakeMove(4, P1_MOVE);
	value = gse.CountNFromLocation(b.StateAccess(), 5, 0, P1_MOVE, 3);
	EXPECT_EQ(value, 1);
	value = gse.CountNFromLocation(b.StateAccess(), 5, 0, P1_MOVE, 2);
	EXPECT_EQ(value, 1);

	//	Down to right
	b = Board(6, 6, 4);
	b.MakeMove(4, P1_MOVE);
	b.MakeMove(4, P1_MOVE);
	b.MakeMove(3, P2_MOVE);
	b.MakeMove(3, P2_MOVE);
	b.MakeMove(3, P1_MOVE);
	b.MakeMove(2, P2_MOVE);
	b.MakeMove(2, P2_MOVE);
	b.MakeMove(2, P2_MOVE);
	b.MakeMove(2, P1_MOVE);
	value = gse.CountNFromLocation(b.StateAccess(), 5, 4, P1_MOVE, 3);
	EXPECT_EQ(value, 1);

	//	Up to left
	b = Board(6, 6, 4);
	b.MakeMove(5, P1_MOVE);
	b.MakeMove(4, P1_MOVE);
	b.MakeMove(4, P1_MOVE);
	b.MakeMove(3, P2_MOVE);
	b.MakeMove(3, P2_MOVE);
	b.MakeMove(3, P1_MOVE);
	b.MakeMove(2, P2_MOVE);
	b.MakeMove(2, P2_MOVE);
	b.MakeMove(2, P2_MOVE);
	value = gse.CountNFromLocation(b.StateAccess(), 2, 1, P1_MOVE, 3);
	EXPECT_EQ(value, 1);

	//	Up to right
	b = Board(6, 6, 4);
	b.MakeMove(1, P1_MOVE);
	b.MakeMove(2, P2_MOVE);
	b.MakeMove(2, P1_MOVE);
	b.MakeMove(3, P2_MOVE);
	b.MakeMove(3, P2_MOVE);
	b.MakeMove(3, P1_MOVE);
	b.MakeMove(4, P2_MOVE);
	b.MakeMove(4, P2_MOVE);
	b.MakeMove(4, P2_MOVE);
	value = gse.CountNFromLocation(b.StateAccess(), 2, 3, P1_MOVE, 3);
	EXPECT_EQ(value, 1);

	//Large test for surrounded point -> Expects 7
	b = Board(6, 6, 4);
	b.MakeMove(1, P1_MOVE);
	b.MakeMove(1, P1_MOVE);
	b.MakeMove(1, P1_MOVE);
	b.MakeMove(1, P1_MOVE);
	b.MakeMove(1, P1_MOVE);
	b.MakeMove(1, P1_MOVE);

	b.MakeMove(2, P1_MOVE);
	b.MakeMove(2, P1_MOVE);
	b.MakeMove(2, P1_MOVE);
	b.MakeMove(2, P1_MOVE);
	b.MakeMove(2, P1_MOVE);
	b.MakeMove(2, P1_MOVE);

	b.MakeMove(3, P1_MOVE);
	b.MakeMove(3, P1_MOVE);

	b.MakeMove(4, P1_MOVE);
	b.MakeMove(4, P1_MOVE);
	b.MakeMove(4, P1_MOVE);
	b.MakeMove(4, P1_MOVE);
	b.MakeMove(4, P1_MOVE);
	b.MakeMove(4, P1_MOVE);

	b.MakeMove(5, P1_MOVE);
	b.MakeMove(5, P1_MOVE);
	b.MakeMove(5, P1_MOVE);
	b.MakeMove(5, P1_MOVE);
	b.MakeMove(5, P1_MOVE);
	b.MakeMove(5, P1_MOVE);
	cout << b.ToString() << endl;
	value = gse.CountNFromLocation(b.StateAccess(), 3, 2, P1_MOVE, 2);
	EXPECT_EQ(value, 7);
	value = gse.CountNFromLocation(b.StateAccess(), 2, 2, P1_MOVE, 2);
	EXPECT_EQ(value, 6);
	value = gse.CountNFromLocation(b.StateAccess(), 4, 2, P1_MOVE, 2);
	EXPECT_EQ(value, 0);
	//Test that P2 has no moves
	value = gse.CountNFromLocation(b.StateAccess(), 3, 2, P2_MOVE, 2);
	EXPECT_EQ(value, 0);
	value = gse.CountNFromLocation(b.StateAccess(), 2, 2, P2_MOVE, 2);
	EXPECT_EQ(value, 0);
	value = gse.CountNFromLocation(b.StateAccess(), 4, 2, P2_MOVE, 2);
	EXPECT_EQ(value, 0);
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
