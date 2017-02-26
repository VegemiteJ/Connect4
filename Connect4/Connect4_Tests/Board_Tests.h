#include "gtest/gtest.h"
#include "Board.h"
#include "DebugLogger.h"

#include <iostream>

using namespace std;

TEST(BoardTests, Constructor)
{
    Board c = Board(5, 1);
    EXPECT_EQ(c.NumRow, 5);
    EXPECT_EQ(c.NumCol, 1);
    EXPECT_EQ(c.MoveCol, -1);
    EXPECT_EQ(c.MoveRow, -1);
    EXPECT_EQ(c.ConnectLength, 4);
    Matrix* state = c.StateAccess();
    EXPECT_NE(state, nullptr);

    Board b = Board();
    EXPECT_EQ(b.NumRow, 0);
    EXPECT_EQ(b.NumCol, 0);
    EXPECT_EQ(c.MoveCol, -1);
    EXPECT_EQ(c.MoveRow, -1);
    state = b.StateAccess();
    EXPECT_NE(state, nullptr);

    Board d = Board(4, 4, 3);
    EXPECT_EQ(d.ConnectLength, 3);
}

TEST(BoardTests, CopyAssignment)
{
    Board b = Board(2, 2);
    Board a = b;
    Matrix state_b = *(b.StateAccess());
    Matrix state_a = *(a.StateAccess());
    
    EXPECT_NE(&state_a, &state_b);

    EXPECT_EQ(a.NumCol, b.NumCol);
    EXPECT_EQ(a.NumRow, b.NumRow);
    EXPECT_EQ(a.MoveRow, b.MoveRow);
    EXPECT_EQ(a.MoveCol, b.MoveCol);
    EXPECT_EQ(a.ConnectLength, b.ConnectLength);

    Board c = Board(2, 2);
    Matrix state_c = *(c.StateAccess());
    Matrix state_c_copy = c.CopyOfState();
    EXPECT_NE(&state_c, &state_c_copy);

    state_c(1, 1) = 5;
    EXPECT_NE(state_c_copy(1, 1), 5);
}

TEST(BoardTests, Movement)
{
    Board a = Board(4,4);
    a.MakeMove(1, P1_MOVE);
    Matrix* state = a.StateAccess();
    EXPECT_EQ((*state)(3, 0), P1_MOVE);
    EXPECT_EQ(a.MoveCol, 0);
    EXPECT_EQ(a.MoveRow, 3);

    a.MakeMove(1, P2_MOVE);
    EXPECT_EQ((*state)(2, 0), P2_MOVE);
    EXPECT_EQ(a.MoveCol, 0);
    EXPECT_EQ(a.MoveRow, 2);

    a.MakeMove(1, P2_MOVE);
    EXPECT_EQ((*state)(2, 0), P2_MOVE);
    EXPECT_EQ(a.MoveCol, 0);
    EXPECT_EQ(a.MoveRow, 1);

    a.MakeMove(1, P1_MOVE);
    EXPECT_EQ((*state)(1, 0), P2_MOVE);
    EXPECT_EQ(a.MoveCol, 0);
    EXPECT_EQ(a.MoveRow, 0);

    a.MakeMove(2, 3, P2_MOVE);
    EXPECT_EQ((*state)(1, 2), P2_MOVE);
    EXPECT_EQ(a.MoveCol, 2);
    EXPECT_EQ(a.MoveRow, 1);

    cout << a.ToString();

    //Expect Failure
    EXPECT_ANY_THROW(a.MakeMove(1, P1_MOVE));
}

TEST(BoardTests, FilledColumns)
{
    Board a = Board(2, 3);
    a.MakeMove(1, P1_MOVE);
    cout << a.ToString();
    a.MakeMove(1, P1_MOVE);
    cout << a.ToString();

    vector<int>* valid = a.GetAllValidMoves();
    vector<int> validMoves = *valid;
    cout << "Valid Moves " << validMoves.size() << ": " << validMoves[0] << "," << validMoves[1] << endl;
    EXPECT_EQ(validMoves.size(), 2);
    delete valid;

    a.MakeMove(3, P2_MOVE);
    a.MakeMove(3, P2_MOVE);
    valid = a.GetAllValidMoves();
    validMoves = *valid;
    EXPECT_EQ(validMoves.size(), 1);
}

TEST(BoardTests, UndoMoves)
{
    Board a = Board(4, 4, 4);
    a.MakeMove(1, P1_MOVE);
    a.MakeMove(1, P1_MOVE);
    cout << a.ToString();
    EXPECT_EQ(a.FilledColumns[0],2);

    a.UnMakeMove(1);
    cout << a.ToString();
    EXPECT_EQ((*a.state)(2, 0), NO_MOVE);
    EXPECT_EQ((*a.state)(3, 0), P1_MOVE);
    EXPECT_EQ(a.FilledColumns[0], 1);
}

TEST(BoardTests, ToString)
{
    using namespace std;

    Board a = Board(4, 4);
    //Expect roughly this layout - need to manually check
    string expects = "    1   2   3   4";
          expects += "  -----------------";
          expects += "1 |   |   |   |   |";
          expects += "  -----------------";
          expects += "2 |   |   |   |   |";
          expects += "  -----------------";
          expects += "3 |   |   |   |   |";
          expects += "  -----------------";
          expects += "4 |   |   |   |   |";
          expects += "  -----------------";
    cout << a.ToString();

    Board b = Board(8, 8);
    cout << b.ToString();

    GTEST_SUCCESS_("Check it matches");
}