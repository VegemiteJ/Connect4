// Connect4.cpp : Defines the entry point for the console application.
//

#include "Game.h"
#include "Board.h"
#include "Player.h"
//#include "ServerSocketSet.h"
//#include "ClientSocketSet.h"
#include "Consts.h"
#include <iostream>
#include <string>

int verbose = -1;

using namespace std;

int main(int argc, const char** argv)
{
	Params p;
	p.ParseParams(argc, argv);

	Game game(&p);
	game.play();
	game.PrintGameSequence();
}