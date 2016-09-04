#include "GameState.h"
#include "Node.h"
#include "MiniMaxPlayer.h"
#include "board.h"
#include "consts.h"
#include "ColourDef.h"
#include "Params.h"
#include "PrintConsole.h"
#include "Game.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include <thread>


int verbose = 4;

using namespace std;


int main(int argc, const char** argv)
{
	Params* settings = new Params();

	settings->ParseParams(argc, argv);

	cout << "Player1: " << settings->p1 << endl;
	cout << "Player1 Param: " << settings->aiParams1 << endl;
	cout << "Player1 time: " << settings->idTime1 << endl;
	cout << "Player1 maxDepth: " << settings->itrDepth1 << endl;
	cout << "Player1 Node: " << settings->heuristic1 << endl;
	cout << "Player1 randSwaps: " << settings->randSwaps1 << endl;

	cout << "Player2: " << settings->p2 << endl;
	cout << "Player2 Param: " << settings->aiParams2 << endl;
	cout << "Player2 time: " << settings->idTime2 << endl;
	cout << "Player2 maxDepth: " << settings->itrDepth2 << endl;
	cout << "Player2 Node: " << settings->heuristic2 << endl;
	cout << "Player2 randSwaps: " << settings->randSwaps2 << endl;

	cout << "Initial board state: " << settings->bs << endl;
	cout << "Output File: " << settings->of << endl;
	verbose = settings->verbosity;
	cout << "Verbose level: " << verbose << endl;

	Game* newGame = new Game(settings);
	newGame->play();
	newGame->PrintGameSequence();
}