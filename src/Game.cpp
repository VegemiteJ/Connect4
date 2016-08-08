#include "Game.h"
#include "Board.h"
#include "LocalPlayer.h"
//#include "NetworkPlayer.h"
#include "RandomPlayer.h"
#include "MiniMaxPlayer.h"
#include "Consts.h"
#include <iostream>
#include <cstdlib>
#include <random>
#include <memory>
#include <chrono>
#include <functional>
#include <time.h>

using namespace std;

Game::Game(bool isServer) {
	const int numRows = 6;
	const int numCols = 7;

	moveSequence = new int[numRows*numCols]();

	board = new Board(numRows, numCols);

	turnCounter = 0;
	int start;
	
	setPlayers(numRows, numCols, isServer);

	//Perform decision as to who goes first, p1 or p2?
	//	Only relevant for networked game.
	//	TODO: Abstract details away into networked game setup func.
	if (isServer)
	{

		start = detStart();				//User inputs player 1
		cout << "Start: " << start << endl;
		started = start;
		p1->turn = start;
		p1->initialise();
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
	if (verbose>3) {
		cout << "p1 : Player id: " << ((p1->id == 0) ? "Local" : "Network") << " Turn: " << p1->turn << endl;
		cout << "p1 : Player id: " << ((p2->id == 0) ? "Local" : "Network") << " Turn: " << p2->turn << endl;
	}
}

//Create two new players
void Game::setPlayers(int numRows, int numCols, bool isServer)
{
	//p1 = new NetworkPlayer(numRows, numCols, board, isServer);
	p1 = new LocalPlayer(numRows, numCols, board);
	//p1 = new MiniMaxPlayer(numCols, numRows, board, NULL, 0, 0);	//iAlg is 0 -> Alpha beta else minimax
	p2 = new MiniMaxPlayer(numCols, numRows, board, NULL, 1, 0);
}

//Used in networked games
void Game::cleanup()
{
	if (verbose >3)
		cout << "Called Cleanup: " << p2->id <<  endl;
	if (p2->id == 1)
	{
		if (verbose >3)
			cout << "Valid" << endl;
		//NetworkPlayer* p = static_cast<NetworkPlayer*>(p1);
		p2->Exit(true);
	}
}

Game::~Game() 
{
	delete[] moveSequence;
}

Game::Game( const Game &obj ) {}

//Return 0 if p1 starts, 1 if p2 starts
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
		//Player 1s Turn----------------------------------------
		cout << "Player1 turn" << endl;
		int choice;
		choice = p1->play(true);
		choice--;
		while(!board->checkValidMove(choice)){
			choice = p1->play(false);
			choice--;
		}

		// Place a token in the selected valid column
		moveSequence[turnCounter] = choice+1;
		board->update_cell(choice, 'X');
		board->checkWin(choice, 'X');
		turnCounter++;
		board->print(board->getBoardState(0)->LastMoveRow, board->getBoardState(0)->LastMoveCol);

		//Don't ask for player 2 move if 1 wins
		if (board->hasWon == true) {break;}

		//Player 2s Turn----------------------------------------
		cout << "Player2 turn" << endl;
		choice = p2->play(true);
		choice--;
		while(!board->checkValidMove(choice)){
			choice = p2->play(false);
			choice--;
		}
		moveSequence[turnCounter] = choice+1;
		board->update_cell(choice, 'O');
		board->checkWin(choice, 'O');
		turnCounter++;
		board->print(board->getBoardState(0)->LastMoveRow, board->getBoardState(0)->LastMoveCol);
	}

	// Output winner
	if (turnCounter%2 != 0)
		cout << "X wins!" << endl;
	else
		cout << "O wins!" << endl;

	cleanup();
}

void Game::PrintGameSequence()
{
	int count = 0;
	int* size = board->getSize();

	cout << "Printing the game..." << endl;
	while( count < size[0]*size[1] && moveSequence[count] != 0 )	//Double check for safety
	{
		(count != 0) ? (cout << "," << moveSequence[count++]) : (cout << moveSequence[count++]); 
	}

	delete[] size;
}