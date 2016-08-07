#include "Board.h"
#include "ColourDef.h"
#include "consts.h"

Board::Board(int numRowsi, int numColsi) : numMoves(0)
{
	numRows = numRowsi;
	numCols = numColsi;
	if (verbose > 3)
		cout << "Dimensions: " << numRows << " " << numCols << endl;
	state = new GameState(numRows, numCols);

	resetBoard();
	hasWon = false;
}

Board::~Board() 
{
	cout << "Cleaning Board" << endl;
	delete state;
}

// Prints the board layout
void Board::print()
{
	state->print();
}

// Prints the board layout and current move as yellow
void Board::print(int row, int col)
{
	state->print(row, col);
}

// Insert a move into the 'lowest' slot in the specified column
// Also checks whether it is occupied
void Board::update_cell(int col, char tokenIn)
{	
	state->update_cell(col, tokenIn);
	numMoves++;
}

int Board::getLast()
{
	return lastMove;
}

// Sets the entire board to a space (empty)
void Board::resetBoard()
{
	for (int i=0; i<numRows; i++){
		for (int j=0; j<numCols; j++){
			state->cell_array[i][j] = ' ';
		}
	}
}

// Checks whether the board is full or not 
// Only checks the first (top) row, as all the bottom ones get filled first
bool Board::checkFull()
{
	for (int i=0; i<numCols; i++)
		if (state->cell_array[0][i] == ' ')
			return false;

	return true;
}

bool Board::checkValidMove(int col) 
{
	return state->checkValidMove(col);
}

// Needs to check for four consecutive tokens
// of the same symbol ('O', 'X') in any row, column or diagonal
// Can be made more efficient by only searching from the most recently placed dude
// Taking into account edge cases??
void Board::checkWin(int colIn, char tokenIn)
{
	if(state->checkWin(colIn, tokenIn))
		hasWon = true;

}

bool Board::doCheck(int row, int col, char tokenIn) 
{
	return state->doCheck(row, col, tokenIn);
}

char** Board::getBoardState()
{
	return state->cell_array;
}

int* Board::getSize()
{
	int* size = new int[2];
	size[0] = numRows;
	size[1] = numCols;
	return size;
}

GameState* Board::getBoardState(int dummy)
{
	return state;
}