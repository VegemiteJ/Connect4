#include "NetworkPlayer.h"
#include "LocalPlayer.h"
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

NetworkPlayer::~NetworkPlayer() {}

void NetworkPlayer::Connect()
{
	if (isServer)
	{
		cout << "Enter Port to use: ";
		string port;
		getline(cin, port);
		cout << "Port Selected: " << port << endl;
		cout << "Waiting for client..." << endl;
		server = new ServerSocketSet(port);
		cout << "Connected!" << endl;

		//Start determination protocol
		string start;
		cout << "Who starts? Enter 0 for this player, or 1 for the other player: ";
		getline(cin, start);
		if (start == "0") {
			turn = true;
		} else {
			turn = false;
		}

		int status = server->sendMessage(start);
		if (status != 0) { 
			cout << "Error sending...";
			exit(1);
		}
	}
	else 
	{
		cout << "Establishing LocalPlayer..." << endl;
		player  = new LocalPlayer(numRows, numColumns, board);
		cout << "Done" << endl;

		cout << "Enter IP in dotted decimal format e.g. \"127.0.0.1\": ";
		string hostname;
		getline(cin, hostname);
		cout << "\nEnter Port of host: ";
		string port;
		getline(cin, port);

		cout << "Connecting..." << endl;
		client = new ClientSocketSet(hostname, port);
		cout << "Connected!" << endl;

		//Start determination protocol
		char* whoStarts = client->receiveMessage();
		string start = string(whoStarts);
		if (start == "0") {
			turn = false;
		} else {
			turn = true;
		}
	}
	string stat = turn ? "Me" : "Other";
	cout << "Turn is: " << stat << endl;
}



int NetworkPlayer::play(bool valid) 
{
	return 0;
}