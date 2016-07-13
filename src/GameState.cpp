#include "GameState.h"
#include "ColourDef.h"
#include <iostream>

using namespace std;

void GameState::initCellArray()
{
	cell_array = new char*[numRows];
	for (int i = 0; i < numRows; i++) {
		cell_array[i] = new char[numCols];
	}
	for (int i=0; i<numRows; i++){
		for (int j=0; j<numCols; j++){
			cell_array[i][j] = ' ';
		}
	}
}

GameState::GameState(char** prev_cell_array, int inumRows, int inumCols) :
	numRows(inumRows), numCols(inumCols)
{
	LastMoveRow = -1;
	initCellArray();
	//New copy
	for (int i=0; i<numRows; i++)
	{
		for (int j=0; j<numCols;j++)
		{
			cell_array[i][j] = prev_cell_array[i][j];
		}
	}
}

GameState::GameState(GameState* prev, int row, int col, int turn)
{
	LastMoveRow = -1;
	numRows = prev->numRows;
	numCols = prev->numCols;

	initCellArray();

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

GameState::GameState(GameState* prev, int col, int turn)
{
	LastMoveRow = -1;
	numRows = prev->numRows;
	numCols = prev->numCols;

	initCellArray();

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
	
	cout << endl << endl;
	LastMoveCol = col;
}


GameState::GameState(int inumRows, int inumCols) :
	numRows(inumRows), numCols(inumCols)
{
	LastMoveRow = -1;
	LastMoveCol = -1;
	initCellArray();
}

GameState::~GameState()
{
	for (int i=0; i<numRows; i++)
	{
		delete[] cell_array[i];	
	}
	delete[] cell_array;
	
}

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

bool GameState::checkValidMove(int col) {
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
		if (cell_array[rowIn][colIn] == ' ')
			break;
	}
	rowIn++;

	// Check winning positions
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
	if (rowIn < 3)
	{
		bool sameToken = true;
		// Check the cells below for consecutiveness
		for (int i=rowIn; i<rowIn+4; i++)
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
	for (int i=0; i<numCols-3; i++)
	{
		if (cell_array[rowIn][i+0] == tokenIn && cell_array[rowIn][i+1] == tokenIn && 
			cell_array[rowIn][i+2] == tokenIn && cell_array[rowIn][i+3] == tokenIn)
		{
			return true;
		}
	}
	return false;
}

// --- Check Diagonal by running up LeftUpper, RightDown followed by RightUpper, LeftDown ---
// If either the sum of tokens matching tokenIn along LU,RD or along RU,LD is equal to 4 there is a winner
bool GameState::checkDiag(int rowIn, int colIn, char tokenIn) 
{
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
	if (leftRun == 4) {
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
	if (rightRun == 4) {
		hasWon = true;
		return true;
	}
	return hasWon;
}

bool GameState::doCheck(int row, int col, char tokenIn) {
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