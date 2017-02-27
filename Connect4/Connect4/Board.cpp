
#include "Board.h"
#include "ColourDef.h"

#include <sstream>
#include <iostream>

using namespace std;

#pragma region Constructors

Board::Board()
{
    state = new Matrix(0, 0);
    FilledColumns = new int[0]{ };
    NumRow = 0;
    NumCol = 0;
    MoveRow = -1;
    MoveCol = -1;
    NumMovesTotal = 0;
    LastMove = NO_MOVE;
    ConnectLength = 0;
}

void Board::CheckValid(Move p)
{
    if (p != P1_MOVE && p != P2_MOVE)
    {
        throw new exception("Made a move that was not P1 or P2");
    }
}

Board::Board(int _row, int _col, int _connectLength)
    : Board(_row,_col)
{
    ConnectLength = _connectLength;
}

Board::Board(int _row, int _col)
{
    state = new Matrix(_row, _col);
    FilledColumns = new int[_col] {0};
    NumRow = _row;
    NumCol = _col;
    MoveRow = -1;
    MoveCol = -1;
    NumMovesTotal = 0;
    LastMove = NO_MOVE;
    ConnectLength = 4;
}

void swap(Board & first, Board & second)
{
	using std::swap;

	swap(first.NumCol, second.NumCol);
	swap(first.NumRow, second.NumRow);
    swap(first.MoveCol, second.MoveCol);
    swap(first.MoveRow, second.MoveRow);
    swap(first.NumMovesTotal, second.NumMovesTotal);
    swap(first.ConnectLength, second.ConnectLength);
    swap(first.FilledColumns, second.FilledColumns);
	swap(first.state, second.state);
}


Board & Board::operator=(Board & other)
{
	swap(*this, other);
	return *this;
}

Board::Board(const Board & other)
{
    //Uses copy of matrix
    state = other.state;
    NumRow = other.NumRow;
    NumCol = other.NumCol;
    MoveRow = other.MoveRow;
    MoveCol = other.MoveCol;
    NumMovesTotal = other.NumMovesTotal;
    ConnectLength = other.ConnectLength;
    FilledColumns = new int[NumCol] {0};
    std::copy(other.FilledColumns, other.FilledColumns + other.NumCol, FilledColumns);
}

Board::Board(Board && other)
    : Board()
{
    swap(*this, other);
}

Board::~Board() 
{
    delete[] FilledColumns;
}

#pragma endregion

string Board::ToString()
{
    stringstream ss;
    // x axis labels
    ss << "    ";
    for (int i = 1; i<NumCol + 1; i++)
    {
        ss << i << "   ";
    }
	ss << endl;

    // Row separators
    ss << "  --";
    for (int i = 1; i < NumCol; i++)
    {
        ss << "----";
    }
    ss << "---";
    ss << endl;

    for (int x = 0; x < NumRow; x++)
    {
        // y axis labels
        ss << x + 1 << " " << "| ";

        // Column separators
        for (int y = 0; y < NumCol; y++)
        {
            //Deduce the player who moved
            string moveChar;
            if ((*state)(x, y) == P1_MOVE)
                moveChar = P1_MOVE_MARKER;
            else if ((*state)(x, y) == P2_MOVE)
                moveChar = P2_MOVE_MARKER;
            else
                moveChar = ' ';

            if (moveChar == P1_MOVE_MARKER) {
                ss << ANSI_RED;
            }
            else {
                ss << ANSI_GREEN;
            }

            ss << moveChar << ANSI_RESET << " | ";
        }

        // Row separators
        ss << endl << "  --";
		for (int i = 1; i < NumCol; i++)
		{
			ss << "----";
		}
        ss << "---";
        ss << endl;
    }
    string result = ss.str();
    ss.clear();

	return result;
}


Matrix * Board::StateAccess()
{
	return state;
}

Matrix Board::CopyOfState()
{
	return Matrix(*state);
}

vector<int>* Board::GetAllValidMoves()
{
    vector<int>* validMoves = new vector<int>();

    //Iterate across columns at row [0] checking they are empty
    for (int i = 0; i < NumCol; i++)
    {
        if ((*state)(0, i) == NO_MOVE)
        {
            validMoves->push_back(i);
        }
    }

    return validMoves;
}

/// <summary>
/// Given 1-indexed move, update to 0-indexed location
/// </summary>
/// <param name="col">The col.</param>
/// <param name="p">The player as enum P1_MOVE or P2_MOVE</param>
void Board::MakeMove(int col, Move p)
{
    NumMovesTotal++;
    LastMove = p;
    MoveCol = col-1;
    MoveRow = NumRow - FilledColumns[col - 1] - 1;
    (*state)(MoveRow, col-1) = p;
    FilledColumns[col-1]++;
}

/// <summary>
/// Given 1-indexed move col+row, update to 0-indexed location
/// </summary>
/// <param name="row">The row.</param>
/// <param name="col">The col.</param>
/// <param name="p">The player as enum P1_MOVE or P2_MOVE</param>
void Board::MakeMove(int row, int col, Move p)
{
    NumMovesTotal++;
    LastMove = p;
    MoveCol = col - 1;
    MoveRow = row - 1;
    (*state)(row-1, col-1) = p;
}

/// <summary>
/// Undos the last move at column i
/// </summary>
/// <param name="col">The col.</param>
void Board::UnMakeMove(int col)
{
    NumMovesTotal--;
    LastMove = NO_MOVE;
    MoveCol = col - 1;
    MoveRow = NumRow - FilledColumns[col - 1];
    (*state)(MoveRow, col - 1) = NO_MOVE;
    FilledColumns[col - 1]--;
}

/// <summary>
/// Undos the last move at column and row
/// </summary>
/// <param name="row">The row.</param>
/// <param name="col">The col.</param>
void Board::UnMakeMove(int row, int col)
{
    NumMovesTotal--;
    LastMove = NO_MOVE;
    MoveCol = col - 1;
    MoveRow = col - 1;
    (*state)(row - 1, col - 1) = NO_MOVE;
}
