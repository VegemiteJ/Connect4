#ifndef LOCALPLAYER_H
#define LOCALPLAYER_H

#include "Player.h"

using namespace std;

class LocalPlayer: public Player
{
public:
	LocalPlayer(int numRows, int numCols, Board* iboard);
	~LocalPlayer();
	virtual int play(bool valid);
};


#endif // LOCALPLAYER_H 