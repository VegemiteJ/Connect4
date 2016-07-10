#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"

using namespace std;

class Player
{
public:
	Player(int numRows, int numCols, Board* iboard);
	~Player();
	virtual int play(bool valid) = 0;
	virtual void initialise() = 0;
	int turn;
	int id;

protected:
	int numRows;
	int numColumns;
	Board* board;
};


#endif // PLAYER_H 