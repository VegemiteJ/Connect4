#include "Game.h"
#include "Board.h"
#include "Player.h"
#include "ServerSocketSet.h"
#include "ClientSocketSet.h"

// main file for connect-four game

int main(int argc, char** argv)
{
	Game game;
	game.play();
}