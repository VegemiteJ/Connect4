#ifndef GAMH_H
#define GAME_H

#include "Board.h"
#include "Human.h"

class Game
{
public:
	Game();
	void play();

private:
	int turnCounter;

	Board* board;
	Player* p1;
	Player* p2;
};


#endif //	GAME_H