#include "Game.h"
#include "Board.h"
#include "Player.h"
#include "ServerSocketSet.h"
#include "ClientSocketSet.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
	if (argc != 2) {
		cout << "Incorrect usage Enter \"true\" or \"false\". ./Connect4 [isServer?]" << endl;
		exit(1);
	}
	string isServer = string(argv[1]);	//Get if is server
	bool isServ;
	if (isServer == "true" || isServer == "True")
	{
		isServ = true;
	}
	else
	{
		isServ = false;
	}
	Game game = Game(isServ);
	game.play();
}