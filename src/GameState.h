#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState
{
public:
	//Initialise new state given raw ptr to state and dimensions
	GameState(char** prev_cell_array, int numRows, int numCols);
	
	//Initialise new state given previous gamestate and col/row, turn.
	// Caller must ensure column is a valid move..
	// For DEBUG use only...
	// Normal usage uses GameState(GS*, int, int) constructor
	GameState(GameState* prev, int row, int col, int turn);

	//Initialise new state given previous gamestate and col,turn.
	// Caller must ensure column is a valid move via checkValidMove(desired)
	GameState(GameState* prev, int col, int turn);
	
	//Initialise blank board with numRows, numCols dimensions
	GameState(int numRows, int numCols);
	~GameState();

	//Prints the board state
	void print();

	//Prints the board state with last move as yellow
	void print(int col, int row);

	//Returns true if the game state has been completed
	bool completed();
	
	//Determines if last move tokenIn at state->LastMoveRow||LastMoveCol wins
	bool checkWin(char tokenIn);

	//Determines if last move tokenIn in column colIn wins through any metric
	bool checkWin(int colIn, char tokenIn);

	//Determines winner based off of row in and column in
	bool checkWin(int rowIn, int colIn, char tokenIn);
	
	//Determines if last move tokenIn at position rowIn, colIn wins horizontally
	bool checkVert(int rowIn, int colIn, char tokenIn);
	
	//Determines if last token tokenIn wins in rowIn
	bool checkHorz(int rowIn, char tokenIn);

	//Determines if last move tokenIn at position rowIn, colIn wins diagonally
	bool checkDiag(int rowIn, int colIn, char tokenIn);

	//Check if token is present at position row, col. Performs bounds check
	bool doCheck(int row, int col, char token);

	bool checkValidMove(int col);

	//Sets the number of winning elements to check (usually 4)
	void setLength(int length);

	//Attempts to add a token to column col.
	//	Responsibility for valid placement is up to the caller by calling
	//	checkValidMove();
	void update_cell(int col, char tokenIn);
	void update_cell(int row, int col, char tokenIn);

	//Return the internal state
	char** getState();

	//"Zero" (Set to all ' ' spaces) the cell_array
	void initCellArray(bool init);

	//Index of the Row and Col of the last move
	int LastMoveRow;
	int LastMoveCol;

	//Sizes
	int numRows;
	int numCols;
private:
	//Internal storage
	char** cell_array;
	
	//Value is 4 for connect 4. Set by the Game setup. Remains constant throughout
	//	a game
	int connectLength;
};


#endif