#include "Board.h"

Board::Board(int numRowsi, int numColsi)
{
	numRows = numRowsi;
	numCols = numColsi;
	cout << "Dimensions: " << numRows << " " << numCols << endl;
	cell_array = new char*[numRows];
	for (int i = 0; i < numRows; i++) {
		cell_array[i] = new char[numCols];
	}
	resetBoard();
	hasWon = false;
}

// Prints the board layout and current move
void Board::print()
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
			if (y<numCols-1)
				cout << cell_array[x][y] << " | ";
			else
				cout << cell_array[x][y];
		}
		
		// Row separators
		cout << endl << "  --";
		for (int i=1; i<numCols; i++)
			cout << "----";
		cout << endl;
		// cout << endl << "  --------------------------" << endl;
	}
}

// Insert a move into the 'lowest' slot in the specified column
// Also checks whether it is occupied
void Board::update_cell(int col, char tokenIn)
{	
	bool placed = false;
	// for (int row=6; row>0; row--)
	for (int row = numRows-1; row>-1 && placed == false; row--)
	{
		if (cell_array[row][col] == ' ')
		{
			cell_array[row][col] = tokenIn;
			placed = true;
		}
	}
	// If the entire column is filled, output an error 
	if (placed == false)
		cout << "Error, that column is already full, pick another" << endl;
	else
		checkWin(col, tokenIn);
	
	cout << endl << endl;
	print();
}

bool Board::checkValidMove(int col) {
	bool placeable = false;
	for (int row = numRows-1; row>-1 && placeable == false; row--)
	{
		if (cell_array[row][col] == ' ')
			placeable = true;
	}

	if (col < 0 || col > numCols)
		return false;

	// If the entire column is filled, output an error 
	if (placeable == false) {
		cout << "Error, that column is already full, pick another" << endl;
		return false;
	} else {
		return true;
	}
}

// Sets the entire board to a space (empty)
void Board::resetBoard()
{
	for (int i=0; i<numRows; i++){
		for (int j=0; j<numCols; j++){
			cell_array[i][j] = ' ';
		}
	}
		
	print();
}

// Checks whether the board is full or not 
// Only checks the first (top) row, as all the bottom ones get filled first
bool Board::checkFull()
{
	for (int i=0; i<numCols; i++)
		if (cell_array[0][i] == ' ')
			return false;

	return true;
}

// Needs to check for four consecutive tokens
// of the same symbol ('O', 'X') in any row, column or diagonal
// Can be made more efficient by only searching from the most recently placed dude
// Taking into account edge cases??
void Board::checkWin(int colIn, char tokenIn)
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
	checkVert(rowIn, colIn, tokenIn); 
	checkHorz(rowIn, tokenIn);
	cout << "Now checking diag" << endl;
	checkDiag(rowIn, colIn, tokenIn);
	cout << "HasWon?: " << hasWon << endl;
	

}

// --- Check vertical (Count downwards from current position) ---
// and see if 4 in a column.
void Board::checkVert(int rowIn, int colIn, char tokenIn)
{
	if (DEBUG)
		cout << "Checking vertical wins" << endl;
	
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
			hasWon = true;
		}
	}
}

// --- Check horizontal (Check only current row) ---
// If there are 4 in a row at any point, set the win and return
void Board::checkHorz(int rowIn, char tokenIn)
{
	if (DEBUG)
		cout << "Checking horizontal wins" << endl;
	
	// Search any that still have 4 more
	for (int i=0; i<numCols-3; i++)
	{
		if (cell_array[rowIn][i+0] == tokenIn && cell_array[rowIn][i+1] == tokenIn && 
			cell_array[rowIn][i+2] == tokenIn && cell_array[rowIn][i+3] == tokenIn)
		{
			hasWon = true;
			return;
		}
	}
}

// --- Check Diagonal by running up LeftUpper, RightDown followed by RightUpper, LeftDown ---
// If either the sum of tokens matching tokenIn along LU,RD or along RU,LD is equal to 4 there is a winner
void Board::checkDiag(int rowIn, int colIn, char tokenIn) {
	
	//Check leftUp/DownRight diagonals
	//----------------------------------------------
	int leftRun = 1;

	cout << "Checking LeftUP" << endl;
	int leftUpperCount = 1;
	bool stillValid = true;
	while(stillValid) {
		//Calculate new index
		int row = rowIn - leftUpperCount;
		int col = colIn - leftUpperCount;
		cout << "Row: " << row << "Col: " << col << endl;
		
		//Check if in bounds and run token Test
		stillValid = doCheck(row,col,tokenIn);
		if (stillValid) {
			leftUpperCount++;
			leftRun++;
		}
	}

	cout << "Checking RightDown" << endl;
	int rightLowerCount = 1;
	stillValid = true;
	while(stillValid) {
		//Calculate new index
		int row = rowIn + rightLowerCount;
		int col = colIn + rightLowerCount;
		cout << "Row: " << row << "Col: " << col << endl;

		//Check if in bounds and run token Test
		stillValid = doCheck(row,col,tokenIn);
		if (stillValid) {
			rightLowerCount++;
			leftRun++;
		}
	}
	cout << "Left upper results: " << rightLowerCount << ", " << leftRun << endl;
	if (leftRun == 4) {
		hasWon = true;
	}

	//Check rightUP/DownLeft diagonal
	//---------------------------------------------
	int rightRun = 1;

	cout << "Checking RightUP" << endl;
	int rightUpperCount = 1;
	stillValid = true;
	while(stillValid) {
		//Calculate new index
		int row = rowIn - rightUpperCount;
		int col = colIn + rightUpperCount;
		cout << "Row: " << row << "Col: " << col << endl;

		//Check if in bounds and run token Test
		stillValid = doCheck(row,col,tokenIn);
		if (stillValid) {
			rightUpperCount++;
			rightRun++;
		}
	}
	cout << "Right upper results: " << rightUpperCount << ", " << rightRun << endl;
	
	cout << "Checking LeftDown" << endl;
	int leftLowerCount = 1;
	stillValid = true;
	while(stillValid) {
		//Calculate new index
		int row = rowIn + leftLowerCount;
		int col = colIn - leftLowerCount;
		cout << "Row: " << row << "Col: " << col << endl;

		//Check if in bounds and run token Test
		stillValid = doCheck(row,col,tokenIn);
		if (stillValid) {
			leftLowerCount++;
			rightRun++;
		}
	}
	cout << "Left Lower results: " << leftLowerCount << ", " << rightRun << endl;
	if (rightRun == 4) {
		hasWon = true;
	}
}

bool Board::doCheck(int row, int col, char tokenIn) {
	//Check if in bounds
	if (row >= numRows || col >= numCols || row < 0 || col < 0) {
		return false;
	}

	//Perform the token test
	if (cell_array[row][col] == tokenIn) {
		cout << "Token: " << cell_array[row][col] << " matches " << tokenIn << endl;
		return true;
	} else {
		cout << "Token: " << cell_array[row][col] << " does not match " << tokenIn << endl;
		return false;
	}
}