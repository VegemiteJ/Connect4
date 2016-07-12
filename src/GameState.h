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

	int numRows;
	int numCols;
	char** cell_array;

private:
	void initCellArray();
};


#endif