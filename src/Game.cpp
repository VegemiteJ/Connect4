#include "Game.h"
#include "Board.h"
#include "Player.h"
#include <iostream>

using namespace std;

Game::Game() {
	const int numRows = 6;
	const int numCols = 7;
	board = new Board(numRows, numCols);
	
	int turnCounter = 0;

	p1 = new Player(numRows, numCols);
	p2 = new Player(numRows, numCols);
}

void Game::play() {
	// Playing the actual game
	while (board->checkFull() == false && board->hasWon == false)
	{
		cout << "Player1 turn" << endl;
		int choice;
		bool win = false;
		choice = p1->play();

		// Place a token in the selected valid column
		board->update_cell(choice, 'X');
		turnCounter++;

		if (board->hasWon == true) {break;}
		
		cout << "Player2 turn" << endl;
		choice = p2->play();
		board->update_cell(choice, 'O');
		turnCounter++;
	}
	
	// Output winner
	if (turnCounter%2 != 0)
		cout << "X wins!" << endl;
	else
		cout << "O wins!" << endl;
}