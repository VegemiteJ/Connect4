#ifndef NETWORKPLAYER_H
#define NETWORKPLAYER_H

#include "Player.h"
#include "LocalPlayer.h"
#include "ServerSocketSet.h"
#include "ClientSocketSet.h"

using namespace std;

class NetworkPlayer: public Player
{
public:
	NetworkPlayer(int numRows, int numCols, Board* iboard, bool isServer);
	~NetworkPlayer();
	void Connect();
	virtual int play(bool valid);
	virtual void initialise();
	virtual void setFirst();

private:
	LocalPlayer* player;
	ServerSocketSet* server;
	ClientSocketSet* client;
	bool isServer;
	bool firstRun;

	int receiveMove();
	void updateOpponent();
};


#endif // NETWORKPLAYER_H 