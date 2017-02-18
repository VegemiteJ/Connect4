#include "stdafx.h"
#include "GameState.h"
#include "ColourDef.h"
#include "Consts.h"
#include <iostream>

using namespace std;

//Set cell_array to all spaces
void GameState::initCellArray(bool init)
{
	if (!init) {
		cell_array = new char*[numRows];
		for (int i = 0; i < numRows; i++) {
			cell_array[i] = new char[numCols];
		}
	}
	for (int i=0; i<numRows; i++){
		for (int j=0; j<numCols; j++){
			cell_array[i][j] = ' ';
		}
	}
}

//Initialise new state from parent state (Make a fully copy)
GameState::GameState(char** prev_cell_array, int inumRows, int inumCols) :
	LastMoveRow(-1), LastMoveCol(-1), numRows(inumRows),
	numCols(inumCols), cell_array(NULL), connectLength(4)
{
	initCellArray(false);
	//New copy
	for (int i=0; i<numRows; i++)
	{
		for (int j=0; j<numCols;j++)
		{
			cell_array[i][j] = prev_cell_array[i][j];
		}
	}
}

//Initialise new state from parent state (Make a fully copy)
GameState::GameState(GameState* prev, int row, int col, int turn) :
	LastMoveRow(-1), LastMoveCol(-1), numRows(-1),
	numCols(-1), cell_array(NULL), connectLength(4)
{
	numRows = prev->numRows;
	numCols = prev->numCols;

	initCellArray(false);

	//Copy
	for (int i=0; i<numRows; i++)
	{
		for (int j=0; j<numCols;j++)
		{
			cell_array[i][j] = prev->cell_array[i][j];
		}
	}

	//Update new entry
	cell_array[row][col] = (turn==0) ? 'X' : 'O';
	LastMoveRow = row;
	LastMoveCol = col;
}

//Initialise new state from parent state (Make a fully copy)
//	Adds new entry in col. Performs no validity checking, Object is always constructed
//	but will notify when col is an error
GameState::GameState(GameState* prev, int col, int turn) :
	LastMoveRow(-1), LastMoveCol(col), numRows(-1),
	numCols(-1), cell_array(NULL), connectLength(4)
{
	numRows = prev->numRows;
	numCols = prev->numCols;

	initCellArray(false);

	//Copy
	for (int i=0; i<numRows; i++)
	{
		for (int j=0; j<numCols;j++)
		{
			cell_array[i][j] = prev->cell_array[i][j];
		}
	}

	//Update new entry
	bool placed = false;
	// for (int row=6; row>0; row--)
	for (int row = numRows-1; row>-1 && placed == false; row--)
	{
		if (cell_array[row][col] == ' ')
		{
			LastMoveRow = row;
			cell_array[row][col] = (turn==0) ? 'X' : 'O';
			placed = true;
		}
	}
	// If the entire column is filled, output an error 
	if (placed == false)
		cout << "Error, that column is already full, pick another" << endl;
}

//Construct a new blank State
GameState::GameState(int inumRows, int inumCols) :
	LastMoveRow(-1), LastMoveCol(-1), numRows(inumRows),
	numCols(inumCols), cell_array(NULL), connectLength(4)
{
	initCellArray(false);
}

//Delete cell_array
GameState::~GameState()
{
	if (verbose > 4)
		cout << "Called GameState Destructor" << endl;
	for (int i=0; i<numRows; i++) {
		if (verbose > 4)
			cout << "Deleting row: " << i << endl;
		delete[] cell_array[i];
	}
	if (verbose > 4)
		cout << "Deleting Host Array" << endl;
	delete[] cell_array;
}

//Print the game board. p1 is Red 'X', p2 is green 'O'
void GameState::print()
{
	// x axis labels
	cout << "  ";
	for (int i=1; i<numCols+1; i++)
	{
		cout << i << "   ";
	} cout << endl;
	
	for (int x=0; x<numRows; x++) 
	{
		// y axis labels
		cout << x+1 << " ";
		
		// Column separators
		for (int y=0; y<numCols; y++) 
		{
			if (cell_array[x][y] == 'X'){
				cout << ANSI_RED;
			} else {
				cout << ANSI_GREEN;
			}
			if (y<numCols-1){
				cout << cell_array[x][y] << ANSI_RESET << " | ";
			} else {
				cout << cell_array[x][y] << ANSI_RESET;
			}
		}
		
		// Row separators
		cout << endl << "  --";
		for (int i=1; i<numCols; i++)
			cout << "----";
		cout << endl;
		// cout << endl << "  --------------------------" << endl;
	}
}

//As above but print last move at row,col as yellow
void GameState::print(int row, int col)
{
	// x axis labels
	cout << "  ";
	for (int i=1; i<numCols+1; i++)
	{
		cout << i << "   ";
	} cout << endl;
	
	for (int x=0; x<numRows; x++) 
	{
		// y axis labels
		cout << x+1 << " ";
		
		// Column separators
		for (int y=0; y<numCols; y++) 
		{
			if (cell_array[x][y] == 'X'){
				cout << ((x==row && y==col) ? ANSI_YELLOW : ANSI_RED);
			} else {
				cout << ((x==row && y==col) ? ANSI_YELLOW : ANSI_GREEN);
			}
			if (y<numCols-1){
				cout << cell_array[x][y] << ANSI_RESET << " | ";
			} else {
				cout << cell_array[x][y] << ANSI_RESET;
			}
		}
		
		// Row separators
		cout << endl << "  --";
		for (int i=1; i<numCols; i++)
			cout << "----";
		cout << endl;
		// cout << endl << "  --------------------------" << endl;
	}
}

//Returns true if the game board is full
bool GameState::completed()
{
	//For all columns, only check topmost row
	for(int i=0; i<numCols; i++) {
		if (cell_array[0][i] != 'X' && cell_array[0][i] != 'O')
			return false;
	}
	return true;
}

//Return true if player 'X' or 'O' wins
bool GameState::checkWin(char tokenIn)
{
	return checkWin(LastMoveCol, tokenIn);
}

// Needs to check for four consecutive tokens
// of the same symbol ('O', 'X') in any row, column or diagonal
// Can be made more efficient by only searching from the most recently placed dude
// Taking into account edge cases??
bool GameState::checkWin(int colIn, char tokenIn)
{
	// Navigate to current position from the colIn
	int rowIn;
	for (rowIn = numRows-1; rowIn >-1; rowIn--)
	{
		if (cell_array[rowIn][colIn] == ' ') {
			if (rowIn == numRows-1)
				rowIn--;
			break;
		}
	}
	rowIn++;

	// Check winning positions
	bool hasWon;
	hasWon = checkVert(rowIn, colIn, tokenIn); 
	hasWon |= checkHorz(rowIn, tokenIn);
	hasWon |= checkDiag(rowIn, colIn, tokenIn);
	
	return hasWon;
}

//Return true if player 'X' or 'O' wins
bool GameState::checkWin(int rowIn, int colIn, char tokenIn)
{
	bool hasWon;
	hasWon = checkVert(rowIn, colIn, tokenIn); 
	hasWon |= checkHorz(rowIn, tokenIn);
	hasWon |= checkDiag(rowIn, colIn, tokenIn);
	
	return hasWon;
}

// --- Check vertical (Count downwards from current position) ---
// and see if 4 in a column.
bool GameState::checkVert(int rowIn, int colIn, char tokenIn)
{
	//cout << "Checking vertical wins" << endl;
	
	// Only check if there are at least 4 in the current column
	if (rowIn <= numRows - connectLength)
	{
		bool sameToken = true;
		// Check the cells below for consecutiveness
		for (int i=rowIn; i<rowIn+connectLength; i++)
		{
			if (cell_array[i][colIn] != tokenIn)
			{
				sameToken = false;
				break;
			}
		}
		if (sameToken == true)
		{
			return true;
		}
	}
	return false;
}

// --- Check horizontal (Check only current row) ---
// If there are 4 in a row at any point, set the win and return
bool GameState::checkHorz(int rowIn, char tokenIn)
{
	// Search any that still have 4 more
	for (int i=0; i<numCols-(connectLength-1); i++)
	{
		bool status = true;
		for (int j=0; j<connectLength; j++) {
			status = status && (cell_array[rowIn][i+j] == tokenIn);
			if (!status)	//Slight speedup by not performing rest of the checks
				break;
		}
		//If all still true, must have that many in a row
		if (status)
			return true;
	}
	return false;
}

// --- Check Diagonal by running up LeftUpper, RightDown followed by RightUpper, LeftDown ---
// If either the sum of tokens matching tokenIn along LU,RD or along RU,LD is equal to 4 there is a winner
bool GameState::checkDiag(int rowIn, int colIn, char tokenIn) 
{
	if (!doCheck(rowIn,colIn,tokenIn))
		return false;
	bool hasWon = false;

	//Check leftUp/DownRight diagonals
	//----------------------------------------------
	int leftRun = 1;
	//cout << "Checking LeftUP" << endl;
	int leftUpperCount = 1;
	bool stillValid = true;
	while(stillValid) {
		//Calculate new index
		int row = rowIn - leftUpperCount;
		int col = colIn - leftUpperCount;
		//cout << "Row: " << row << "Col: " << col << endl;
		
		//Check if in bounds and run token Test
		stillValid = doCheck(row,col,tokenIn);
		if (stillValid) {
			leftUpperCount++;
			leftRun++;
		}
	}

	//cout << "Checking RightDown" << endl;
	int rightLowerCount = 1;
	stillValid = true;
	while(stillValid) {
		//Calculate new index
		int row = rowIn + rightLowerCount;
		int col = colIn + rightLowerCount;
		//cout << "Row: " << row << "Col: " << col << endl;

		//Check if in bounds and run token Test
		stillValid = doCheck(row,col,tokenIn);
		if (stillValid) {
			rightLowerCount++;
			leftRun++;
		}
	}
	//cout << "Left upper results: " << rightLowerCount << ", " << leftRun << endl;
	if (leftRun >= connectLength) {
		hasWon = true;
		return true;
	}

	//Check rightUP/DownLeft diagonal
	//---------------------------------------------
	int rightRun = 1;

	//cout << "Checking RightUP" << endl;
	int rightUpperCount = 1;
	stillValid = true;
	while(stillValid) {
		//Calculate new index
		int row = rowIn - rightUpperCount;
		int col = colIn + rightUpperCount;
		//cout << "Row: " << row << "Col: " << col << endl;

		//Check if in bounds and run token Test
		stillValid = doCheck(row,col,tokenIn);
		if (stillValid) {
			rightUpperCount++;
			rightRun++;
		}
	}
	//cout << "Right upper results: " << rightUpperCount << ", " << rightRun << endl;
	
	//cout << "Checking LeftDown" << endl;
	int leftLowerCount = 1;
	stillValid = true;
	while(stillValid) {
		//Calculate new index
		int row = rowIn + leftLowerCount;
		int col = colIn - leftLowerCount;
		//cout << "Row: " << row << "Col: " << col << endl;

		//Check if in bounds and run token Test
		stillValid = doCheck(row,col,tokenIn);
		if (stillValid) {
			leftLowerCount++;
			rightRun++;
		}
	}
	//cout << "Left Lower results: " << leftLowerCount << ", " << rightRun << endl;
	if (rightRun >= connectLength) {
		hasWon = true;
		return true;
	}
	return hasWon;
}

//Return true if the value at cell_array[row][col] == tokenIn
bool GameState::doCheck(int row, int col, char tokenIn)
{
	//Check if in bounds
	if (row >= numRows || col >= numCols || row < 0 || col < 0) {
		return false;
	}

	//Perform the token test
	if (cell_array[row][col] == tokenIn) {
		//cout << "Token: " << cell_array[row][col] << " matches " << tokenIn << endl;
		return true;
	} else {
		//cout << "Token: " << cell_array[row][col] << " does not match " << tokenIn << endl;
		return false;
	}
}

//If a move at column col is valid, return true
bool GameState::checkValidMove(int col)
{
	bool placeable = false;
	
	if (col < 0 || col >= numCols)
		return false;

	for (int row = numRows-1; row>-1 && placeable == false; row--)
	{
		if (cell_array[row][col] == ' ')
			placeable = true;
	}

	// If the entire column is filled, output an error 
	if (placeable == false) {
		return false;
	} else {
		return true;
	}
}

//Attempt to place token in column. No guarantee or error flag set if not possible
//	Caller responsible for first calling checkValidMove
void GameState::update_cell(int col, char tokenIn)
{
	bool placed = false;
	for (int row = numRows-1; row>-1 && placed == false; row--)
	{
		if (cell_array[row][col] == ' ')
		{
			cell_array[row][col] = tokenIn;
			placed = true;
			LastMoveRow = row;
			LastMoveCol = col;
		}
	}
}

//Usable for debug uses only. No guarantee of correctness
void GameState::update_cell(int row, int col, char tokenIn)
{
	cell_array[row][col] = tokenIn;
}

//Set the win length of the game board
void GameState::setLength(int length)
{
	connectLength = length;
}

char** GameState::getState()
{
	return cell_array;
}