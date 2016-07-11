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
	int start;
	p1 = new NetworkPlayer(numRows, numCols, board, isServer);

	if (isServer)
	{

		start = detStart();				//User inputs player 1
		cout << "Start: " << start << endl;
		started = start;
		p1->turn = start;
		p1->initialise();
		p2 = new LocalPlayer(numRows, numCols, board);
		if (start == 0){		//Swap as ordering required is Local, Network
			Player* ptemp = p2;
			p2 = p1;
			p1 = ptemp;
			p2->setFirst();
		}
		//Ready to start the game
	} 
	else 
	{
		p1->turn = 0;		//Turn unknown, get from server
		p1->initialise();
		p2 = new LocalPlayer(numRows, numCols, board);
		start = p1->turn;
		started = start;
		if (start == 1){		//Swap as ordering required is Local, Network
			Player* ptemp = p2;
			p2 = p1;
			p1 = ptemp;
			p2->setFirst();
		}
		//Ready to start the game
	}

	//Verify status
	cout << "p1 : Player id: " << ((p1->id == 0) ? "Local" : "Network") << " Turn: " << p1->turn << endl;
	cout << "p1 : Player id: " << ((p2->id == 0) ? "Local" : "Network") << " Turn: " << p2->turn << endl;

}

void Game::cleanup()
{
	cout << "Called Cleanup: " << p2->id <<  endl;
	if (p2->id == 1)
	{
		cout << "Valid" << endl;
		//NetworkPlayer* p = static_cast<NetworkPlayer*>(p1);
		p2->Exit(true);
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

	cleanup();
}