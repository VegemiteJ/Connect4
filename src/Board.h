#ifndef BOARD_H
#define BOARD_H

#define DEBUG true

#include <iostream>
using namespace std;

class Board
{
public:
	Board(int, int);
	
	void print();
	void update_cell(int col, char tokenIn);
	void resetBoard();
	
	bool checkFull();
	void checkWin(int colIn, char tokenIn);
	void checkVert(int rowIn, int colIn, char tokenIn);
	void checkDiag(int rowIn, int colIn, char tokenIn);
	void checkHorz(int rowIn, char tokenIn);
	
	bool hasWon;
	
private:
	int numRows;
	int numCols;
	char** cell_array;
};

#endif // BOARD_H