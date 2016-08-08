#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"

using namespace std;

class Player
{
public:
	Player(int numRows, int numCols, Board* iboard);
	~Player();

	//All player classes must return the column of the move to play (1-indexed)
	virtual int play(bool valid) = 0;

	//	Only used by networking classes
	//	TODO: use reinterpret casts to interpret player* as networkPlayer*
	virtual void initialise() = 0;
	virtual void setFirst() = 0;
	virtual void Exit(bool notify) = 0;
	int turn;
	int id;

protected:
	int numRows;
	int numColumns;
	Board* board;
};


#endif // PLAYER_H 