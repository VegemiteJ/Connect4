#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState
{
public:
	GameState(char** prev_cell_array, int numRows, int numCols);
	GameState(GameState* prev, int row, int col, int turn);

	//When valid row is not known.
	GameState(GameState* prev, int col, int turn);
	GameState(int numRows, int numCols);
	~GameState();

	void print();

	bool checkWin(char tokenIn);
	bool checkWin(int colIn, char tokenIn);
	bool checkVert(int rowIn, int colIn, char tokenIn);
	bool checkDiag(int rowIn, int colIn, char tokenIn);
	bool checkHorz(int rowIn, char tokenIn);
	bool doCheck(int row, int col, char token);

	bool checkValidMove(int col);

	int LastMoveRow;
	int LastMoveCol;

	int numRows;
	int numCols;
	char** cell_array;

private:
	void initCellArray();
};


#endif