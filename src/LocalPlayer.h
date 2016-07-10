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
	virtual void initialise();
	virtual void setFirst();
};


#endif // LOCALPLAYER_H 