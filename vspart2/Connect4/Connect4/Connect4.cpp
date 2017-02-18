// Connect4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"
#include "Board.h"
#include "Player.h"
//#include "ServerSocketSet.h"
//#include "ClientSocketSet.h"
#include "Consts.h"
#include "PrintConsole.h"
#include "Params.h"

#include <iostream>
#include <string>

int verbose = -1;

using namespace std;

int main(int argc, const char** argv)
{
	Params* settings = new Params();
	settings->ParseParams(argc, argv);

	Game* newGame = new Game(settings);
	newGame->play();
	newGame->PrintGameSequence();
}