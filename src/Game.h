#ifndef GAMH_H
#define GAME_H

#define USE_SYS_TYPES_FD_SET
#define WIN32_LEAN_AND_MEAN
#define __USE_W32_SOCKETS
#include "Board.h"
#include "Player.h"

class Game
{
public:
	Game(bool isServer);
	~Game();
	void play();

private:

	void setPlayers(int numRows, int numCols, bool isServer);

	int detStart();
	void cleanup();

	int turnCounter;
	int started;

	Board* board;
	Player* p1;
	Player* p2;
};


#endif //	GAME_H