#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include "GameState.h"

using namespace std;

class Board
{
public:
	//Creates a new blank state
	Board(int numRows, int numCols);
	//Deletes self and state
	~Board();
	//Copy Constructor
	Board( Board &obj );
	
	//Prints the board with rows and columns 1-indexed
	//	Player 1 is red, Player 2 is green
	void print();
	
	//As above with the last move as yellow
	void print(int row, int col);

	//No guarantee on valid move, add to column
	void update_cell(int col, char tokenIn);

	//Check if this column was full
	bool checkValidMove(int col);

	//Set entire board to character ' ' (space)
	void resetBoard();

	//Check if the entire board is full
	bool checkFull();

	//Sets var hasWon to true if tokenIn in colIn wins
	void checkWin(int colIn, char tokenIn);

	//Check if that position is in bounds or if equal to token
	bool doCheck(int row, int col, char token);
	
	//True if someone has won
	bool hasWon;

	//Return the column of the last move
	int getLast();

	//Return a direct pointer to the internal state array
	//	In general GameState* should be used
	char** getBoardState();

	//Returns a standard GameState
	//	Used in board, players and Node for AIs
	GameState* getBoardState(int avoid);
	
	//Tuple of the board size <rows,cols>
	int* getSize();
	
	//Number of moves made so far
	int numMoves;

private:
	Board();

	int numRows;
	int numCols;
	
	//Column of the last move
	int lastMove;
	GameState* state;
};

#endif // BOARD_H