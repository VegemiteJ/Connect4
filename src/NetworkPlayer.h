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
	
	//Connect to Client if server, else vice versa
	void Connect();

	//If not the first run, update opponent with my last move, then receive opponents move
	virtual int play(bool valid);

	//Connect to opponent
	virtual void initialise();

	//Set first run to true
	virtual void setFirst();

	//If notify true, update opponent of last move
	//	Used when server wins and is player 1.
	virtual void Exit(bool notify);

private:
	LocalPlayer* player;
	ServerSocketSet* server;
	ClientSocketSet* client;
	bool isServer;
	bool firstRun;

	//Receive the column of the move
	int receiveMove();

	//Notify opponent of my last move
	void updateOpponent();
};


#endif // NETWORKPLAYER_H 