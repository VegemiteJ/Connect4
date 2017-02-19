#pragma once

#include "Matrix.h"
#include <string>
#include <vector>

using namespace std;

typedef enum Move { NO_MOVE = 0, P1_MOVE = 1, P2_MOVE = 2 };

/// <summary>
/// Container for board state
/// </summary>
class Board
{
private:
	//Holds a matrix object
	Matrix* state;

    int* FilledColumns;

    void CheckValid(Move p);

public:
	int NumRow;
	int NumCol;

    int MoveRow;
    int MoveCol;

#pragma region Constructors
	/// <summary>
	/// Initializes a new instance of the <see cref="Board"/> class.
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

#pragma endregion

#pragma region Accessors

	Matrix* StateAccess();
	Matrix CopyOfState();

#pragma endregion

#pragma region MoveSemantics

    vector<int>* GetAllValidMoves();

    void MakeMove(int col, Move p);
    void MakeMove(int row, int col, Move p);

#pragma endregion


};