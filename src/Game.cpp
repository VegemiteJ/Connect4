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
		int start = detStart();
		cout << "Start: " << start << endl;

		//p1 is me, p2 is connection layer to other player. I am Host
		p1 = new LocalPlayer(numRows, numCols, board);
		p2 = new NetworkPlayer(numRows, numCols, board, true);

		p2->turn = (start == 0) ? false : true;

		if(start == 1) {		//Swap order
			Player* ptemp = p2;
			p2 = p1;
			p1 = ptemp;
			//Order is Now:
			//p1 = NetworkPlayer
			//p2 = LocalPlayer

			cout << "Order: " << p1->turn << endl;
		}
		cout << "Order: " << p2->turn << endl;

	} 
	else 
	{
		//p1 is me, p2 is connection layer to other player, I am not Host
		p1 = new LocalPlayer(numRows, numCols, board);
		p2 = new NetworkPlayer(numRows, numCols, board, false);
		
	}

}

Game::~Game() {}

int Game::detStart()
{
		//Start determination protocol
		string start;
		while (start != "0" && start != "1") {
			cout << "Who starts? Enter 0 for this player, or 1 for the other player: ";
			getline(cin, start);
		}
		return (start == "0") ? 0 : 1;
}

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