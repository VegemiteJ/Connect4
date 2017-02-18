#ifndef GAMH_H
#define GAME_H

#define USE_SYS_TYPES_FD_SET
#define WIN32_LEAN_AND_MEAN
#define __USE_W32_SOCKETS
#include "Board.h"
#include "Player.h"
#include "Params.h"

class Game
{
public:
	//Set up a new game with special parameters if we are a server
	Game(Params* m_settings);
	~Game();

	//Play a game
	void play();

	//Print a sequence of moves played in a game
	void PrintGameSequence();
	
private:
	//Can't create a copy of game
	Game() {}
	Game( const Game &obj );

	//Set the specific players
	//	TODO: eliminate need for numRows, numCols call and request from board
	void setupPlayers();
	
	void setupNetworkedGame();

	//Returns 0 if p1 starts, 1 if p2 starts. Determine the start order by prompting
	//	the user (Server) for input
	int detStart();

	//If the server, notify the client and shutdown the socket
	void cleanup();

	//Set a starting game sequence for testing
	void BoardInit();

	//Increments for each move
	int turnCounter;

	//0 if p1 starts, 1 if p2 starts
	int started;

	//Series of moves that was played in the game
	int* moveSequence;

	Board* board;
	Player* p1;
	Player* p2;
	Params* settings;

	int xMoves;
	int oMoves;
};


#endif //	GAME_H