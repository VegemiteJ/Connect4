#ifndef BOARD_H
#define BOARD_H

#define DEBUG true

#include <iostream>
#include "GameState.h"

using namespace std;

class Board
{
public:
	Board(int numRows, int numCols);
	~Board();
	
	void print();
	void update_cell(int col, char tokenIn);
	bool checkValidMove(int col);
	void resetBoard();
	bool checkFull();

	void checkWin(int colIn, char tokenIn);
	void checkVert(int rowIn, int colIn, char tokenIn);
	void checkDiag(int rowIn, int colIn, char tokenIn);
	void checkHorz(int rowIn, char tokenIn);
	bool doCheck(int row, int col, char token);
	
	bool hasWon;

	int getLast();

	char** getBoardState();
	int* getSize();
	
private:
	Board();

	int numRows;
	int numCols;
	int lastMove;
	GameState* state;
};

#endif // BOARD_H