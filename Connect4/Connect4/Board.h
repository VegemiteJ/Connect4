#pragma once

#include "Matrix.h"
#include <string>
#include <vector>

using namespace std;

enum Move { UNFINISHED = -1, NO_MOVE = 0, P1_MOVE = 1, P2_MOVE = 2 };

/// <summary>
/// Container for board state
/// </summary>
class Board
{
private:
	//Holds a matrix object
	Matrix* state;

    #pragma region GoogleTests
    #include "gtest\gtest_prod.h"
    FRIEND_TEST(BoardTests, UndoMoves);
    #pragma endregion

    int* FilledColumns;

	vector<int> validMoves;
    void CheckValid(Move p);

public:
	int NumRow;
	int NumCol;

    int NumMovesTotal;

    int MoveRow;
    int MoveCol;
    Move LastMove;

    int ConnectLength;

#pragma region Constructors    
    /// <summary>
    /// Sets the winning length via connectLength
    /// </summary>
    /// <param name="_row">The row.</param>
    /// <param name="_col">The col.</param>
    /// <param name="_connectLength">Length of the connect.</param>
    Board(int _row, int _col, int _connectLength);


	/// <summary>
	/// Default size of 4 in a row to win
	/// </summary>
	/// <param name="_row">The number of rows</param>
	/// <param name="_col">The number of cols</param>
	Board(int _row, int _col);

    Board();

	friend void swap(Board& first, Board& second);
	Board& operator=(Board& other);
    Board(const Board& other);
    Board(Board&& other);
	~Board();
#pragma endregion

#pragma region Print

	string ToString();
	string ToString(int indentLvl);

#pragma endregion

#pragma region Accessors

	Matrix* StateAccess();
	Matrix CopyOfState();

#pragma endregion

#pragma region MoveSemantics

    vector<int>& GetAllValidMoves();
    

    /// <summary>
    /// Given 1-indexed move, update to 0-indexed location
    /// </summary>
    /// <param name="col">The col.</param>
    /// <param name="p">The player as enum P1_MOVE or P2_MOVE</param>
    void MakeMove(int col, Move p);    

    /// <summary>
    /// Given 1-indexed move col+row, update to 0-indexed location
    /// </summary>
    /// <param name="row">The row.</param>
    /// <param name="col">The col.</param>
    /// <param name="p">The player as enum P1_MOVE or P2_MOVE</param>
    void MakeMove(int row, int col, Move p);

    void UnMakeMove(int col);
    void UnMakeMove(int row, int col);

#pragma endregion


};