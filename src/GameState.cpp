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
}

GameState::GameState(GameState* prev, int col, int turn)
{
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
			cell_array[row][col] = (turn==0) ? 'X' : 'O';
			placed = true;
		}
	}
	// If the entire column is filled, output an error 
	if (placed == false)
		cout << "Error, that column is already full, pick another" << endl;
	
	cout << endl << endl;
}


GameState::GameState(int inumRows, int inumCols) :
	numRows(inumRows), numCols(inumCols)
{
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