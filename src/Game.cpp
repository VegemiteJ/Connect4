#include "stdafx.h"
#include "Game.h"
#include "Board.h"
#include "LocalPlayer.h"
//#include "NetworkPlayer.h"
#include "RandomPlayer.h"
#include "MiniMaxPlayer.h"
#include "Consts.h"
#include "PrintConsole.h"

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <random>
#include <memory>
#include <chrono>
#include <functional>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

Game::Game(Params* m_settings): turnCounter(0), started(0),
 	moveSequence(NULL), board(NULL), p1(NULL), p2(NULL), 
 	settings(m_settings), xMoves(0), oMoves(0)
{
	PrintConsole("Creating new game\n", 3);
	//Setup move sequence, turn counter, who starts var
	//Setup board
	//Setup players -> pass parameters to ai as necessary
	//	Also for networked game sanity check player selection and ordering
	//	Abstract network setup game into seperate function as necessary
	
	//Default size
	int nRows = 6;
	int nCols = 7;
	board = new Board(nRows,nCols);

	//In future BoardInit() reads in board size and starting positions 
	//	if any from the file included in the parameters settings file.

	int* size = board->getSize();
	nRows = size[0];
	nCols = size[1];
	delete[] size;

	moveSequence = new int[nRows*nCols]();

	//Determine if networked game
	if (settings->networkGame) {
		setupNetworkedGame();
	} else {
		setupPlayers();
	}

	PrintConsole("Player 1 is: " + to_string(p1->id) + "\n",3);
	PrintConsole("Player 2 is: " + to_string(p2->id) + "\n",3);
	BoardInit();
}

//Create two new players
void Game::setupPlayers()
{
	if (settings->p1 == "lp") {
		p1 = new LocalPlayer(board);
	}else if (settings->p1 == "rp") {
		p1 = new RandomPlayer(board);
	}else if (settings->p1 == "ai") {
		//Determine minimax or alphabeta and other params
		p1 = new MiniMaxPlayer(board,NULL,0,settings->heuristic1,\
		settings->randSwaps1,settings->aiParams1,settings->idTime1,settings->itrDepth1);
	}else {
		//Error somehow
		PrintConsole("Error: Game setup - Invalid player option\n",-1000);
	}
	if (settings->p2 == "lp") {
		p2 = new LocalPlayer(board);
	}else if (settings->p2 == "rp") {
		p2 = new RandomPlayer(board);
	}else if (settings->p2 == "ai") {
		//Determine minimax or alphabeta and other params
		p2 = new MiniMaxPlayer(board,NULL,1,settings->heuristic2,\
		settings->randSwaps2,settings->aiParams2,settings->idTime2,settings->itrDepth2);
	}else {
		//Error somehow
		PrintConsole("Error: Game setup - Invalid player option\n",-1000);
	}
}

void Game::setupNetworkedGame()
{
	PrintConsole("Network Setup called\n",3);
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

//Game::Game( const Game &obj ) {}

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
	if (p1 == NULL || p2 == NULL) {
		PrintConsole("Error: Game - p1 and/or p2 not set before play()\n",-1000);
	}

	if (verbose >= -1)
		board->print();
	while (board->checkFull() == false && board->hasWon == false)
	{
		//Player 1s Turn----------------------------------------
		if (verbose >= -1)
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
		xMoves++;
		if (verbose >= -1)
			board->print(board->getBoardState(0)->LastMoveRow, board->getBoardState(0)->LastMoveCol);

		//Don't ask for player 2 move if 1 wins
		if (board->hasWon == true) {break;}

		//Player 2s Turn----------------------------------------
		if (verbose >= -1)		
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
		oMoves++;
		if (verbose >= -1)
			board->print(board->getBoardState(0)->LastMoveRow, board->getBoardState(0)->LastMoveCol);
	}

	if (verbose >=-2) {
		board->print(board->getBoardState(0)->LastMoveRow, board->getBoardState(0)->LastMoveCol);
	}

	// Output winner
	if (verbose >= -2) {
		if (board->hasWon) {
			if (turnCounter%2 != 0) {
				cout << "X wins!" << endl;
			} else {
				cout << "O wins!" << endl;
			}
		} else {
			cout << "Draw!" << endl;
		}
	}

	PrintConsole("xMoves: " + to_string(xMoves) + "\n",-3);
	PrintConsole("oMoves: " + to_string(oMoves) + "\n",-3);
	PrintConsole("tCount: " + to_string(turnCounter) + "\n",-3);

	cleanup();
}

void Game::PrintGameSequence()
{
	int count = 0;
	int* size = board->getSize();
	stringstream ss;

	//cout << "Printing the game..." << endl;
	while( count < size[0]*size[1] && moveSequence[count] != 0 )	//Double check for safety
	{
		(count != 0) ? (ss << "," << moveSequence[count++]) : (ss << moveSequence[count++]); 
	}

	//If even number of moves, O wins... unless !hasWon
	char winner;
	if (!board->hasWon) {
		winner = 'D';
	} else if (count%2 == 0) {
		winner = 'O';
	} else {
		winner = 'X';
	}

	ostringstream out;
	out << "\n" << winner << "," << count << "\n";
	string winnerstr = out.str();
	string moveSeq = ss.str();
	
	PrintConsole(winnerstr,-2);

	if (settings->of != "") {
		string filename = settings->of;
		ofstream outfile;
		outfile.open(filename, ios::out | ios::app);
		while (!outfile.is_open()){
			outfile.open(filename, ios::out | ios::app);
		}
		outfile << winnerstr << moveSeq;
		outfile.close();
	}

	delete[] size;
}

void Game::BoardInit()
{
	board->update_cell(3,'X');
	turnCounter++;
	board->update_cell(6,'O');
	turnCounter++;
}

/*
	const int numRows = 6;
	const int numCols = 7;

	moveSequence = new int[numRows*numCols]();

	board = new Board(numRows, numCols);
	BoardInit();

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
	*/