#ifndef NETWORKPLAYER_H
#define NETWORKPLAYER_H

#include "Player.h"
#include "ServerSocketSet.h"
#include "ClientSocketSet.h"

using namespace std;

class NetworkPlayer: public Player
{
public:
	NetworkPlayer(int numRows, int numCols, Board* iboard, bool isServer);
	void Connect();
	virtual int play(bool valid);

private:
	ServerSocketSet* server;
	ClientSocketSet* client;
	bool isServer;

};


#endif // NETWORKPLAYER_H 