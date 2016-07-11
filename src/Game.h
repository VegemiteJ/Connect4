#ifndef GAMH_H
#define GAME_H

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