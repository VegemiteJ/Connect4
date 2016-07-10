#include "Game.h"
#include "Board.h"
#include "LocalPlayer.h"
#include "NetworkPlayer.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Game::Game(bool isServer) {
	const int numRows = 6;
	const int numCols = 7;
	board = new Board(numRows, numCols);
	
	int turnCounter = 0;

	if (isServer)
	{
		//p1 is me, p2 is connection layer to other player. I am Host
		p1 = new LocalPlayer(numRows, numCols, board);
		p2 = new NetworkPlayer(numRows, numCols, board, true);		
	} 
	else 
	{
		//p1 is me, p2 is connection layer to other player, I am not Host
		p1 = new LocalPlayer(numRows, numCols, board);
		p2 = new NetworkPlayer(numRows, numCols, board, false);
	}

}

Game::~Game() {}

void Game::play() {
	// Playing the actual game
	board->print();
	while (board->checkFull() == false && board->hasWon == false)
	{
		cout << "Player1 turn" << endl;
		int choice;
		bool win = false;
		choice = p1->play(true);
		choice--;
		while(!board->checkValidMove(choice)){
			choice = p1->play(false);
			choice--;
		}

		// Place a token in the selected valid column
		board->update_cell(choice, 'X');
		turnCounter++;
		board->print();

		if (board->hasWon == true) {break;}
		cout << "Player2 turn" << endl;
		choice = p2->play(true);
		choice--;
		while(!board->checkValidMove(choice)){
			choice = p2->play(false);
			choice--;
		}
		board->update_cell(choice, 'O');
		turnCounter++;
		board->print();
	}
	
	// Output winner
	if (turnCounter%2 != 0)
		cout << "X wins!" << endl;
	else
		cout << "O wins!" << endl;
}