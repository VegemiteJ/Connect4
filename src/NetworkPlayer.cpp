#include "NetworkPlayer.h"
#include "ServerSocketSet.h"
#include "ClientSocketSet.h"
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

NetworkPlayer::NetworkPlayer(int numRows, int numCols, Board* iboard, bool isS)
	: Player(numRows, numCols, iboard) 
{
	isServer = isS;
	Connect();
}

void NetworkPlayer::Connect()
{
	if (isServer)
	{
		cout << "Enter Port to use: ";
		string port;
		getline(cin, port);
		cout << "Port Selected: " << port << endl;
		server = new ServerSocketSet(port);
	}
}

int NetworkPlayer::play(bool valid) 
{
	return 0;
}