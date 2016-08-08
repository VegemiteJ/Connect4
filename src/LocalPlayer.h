#ifndef LOCALPLAYER_H
#define LOCALPLAYER_H

#include "Player.h"

using namespace std;

class LocalPlayer: public Player
{
public:
	LocalPlayer(int numRows, int numCols, Board* iboard);
	~LocalPlayer();

	//Prompt the User for a move via CLI
	virtual int play(bool valid);

	//Inherited unused Player functions
	virtual void initialise();
	virtual void setFirst();
	virtual void Exit(bool);
};


#endif // LOCALPLAYER_H 