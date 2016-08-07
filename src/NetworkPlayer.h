#ifndef NETWORKPLAYER_H
#define NETWORKPLAYER_H

#define USE_SYS_TYPES_FD_SET
#define WIN32_LEAN_AND_MEAN
#define __USE_W32_SOCKETS
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
	virtual void Exit(bool notify);

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