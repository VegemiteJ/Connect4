#include "Board.h"
#include "Human.h"

// main file for connect-four game

int main()
{
	Board board1;
	
	int choice = 4;
	bool hasWon = false;
	
	int turnCounter = 0;
	// Playing the actual game
	while (board1.checkFull() == false && board1.hasWon == false)
	{
		do
		{
			cout << "Enter a column in which to place your token (1 ... " << COLUMNS << "): " << endl;
			cin >> choice;
		} while (choice < 1 || choice > COLUMNS);
		// Adjust so it fits with array indexing (0-COLUMNS-1)
		choice--;
		
		// Place a token in the selected valid column
		if (turnCounter%2 == 0)
			board1.update_cell(choice, 'X');
		else
			board1.update_cell(choice, 'O');
		
		turnCounter++;
	}
	
	// Output winner
	if (turnCounter%2 != 0)
		cout << "X wins!" << endl;
	else
		cout << "O wins!" << endl;
}