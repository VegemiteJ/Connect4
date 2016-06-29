#ifndef BOARD_H
#define BOARD_H

#define ROWS 6
#define COLUMNS 7
#define DEBUG true

#include <iostream>
using namespace std;

class Board
{
public:
	Board();
	
	void print();
	void update_cell(int col, char tokenIn);
	void resetBoard();
	
	bool checkFull();
	void checkWin(int colIn, char tokenIn);
	void checkVert(int rowIn, int colIn, char tokenIn);
	void checkHorz(int rowIn, char tokenIn);
	
	bool hasWon;
	
private:
	char cell_array[ROWS][COLUMNS];
};

#endif // BOARD_H