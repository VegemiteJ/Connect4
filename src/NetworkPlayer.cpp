#include "stdafx.h"
#include "NetworkPlayer.h"
#include "LocalPlayer.h"
#include "ServerSocketSet.h"
#include "ClientSocketSet.h"
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

NetworkPlayer::NetworkPlayer(int numRows, int numCols, Board* iboard, bool isS)
	: Player(numRows, numCols, iboard), player(NULL), server(NULL), client(NULL)
{
	isServer = isS;
	id = 1;				//Player id
	firstRun = true;
}

NetworkPlayer::~NetworkPlayer() {}

void NetworkPlayer::initialise() 
{
	cout << "Turn: " << turn << endl;
	Connect();
}

void NetworkPlayer::setFirst()
{
	firstRun = false;
}

void NetworkPlayer::Exit(bool notify)
{
	if (notify) {
		cout << "Now updating opponent..." << endl;
		updateOpponent();
	}
}

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
		if (server->errorFlag == 0)
			cout << "Connected!" << endl;

		//Turn must be set by Game class before sending
		string start = (turn == 0) ? "0" : "1";

		int status = server->sendMessage(start);
		if (status == 0) { 
			cout << "Error sending...";
			exit(1);
		}
		cout << "Sent turn: " << start << endl;
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
		if (client->errorFlag == 0)
			cout << "Connected!" << endl;

		//Start determination protocol
		char* whoStarts = client->receiveMessage();
		string start = string(whoStarts);
		turn = (start == "0") ? 0 : 1;
	}
	string stat = (turn==0) ? "Server" : "Client";
	cout << "Turn is: " << stat << endl;
}

void NetworkPlayer::updateOpponent()
{
	string update = to_string(board->getLast()+1);	//Get last move made
	cout << "Sending update column: " << board->getLast()+1 << endl;
	if(isServer)
	{
		int status = server->sendMessage(update);
		if(status == 0) {
			cout << "Error sending..." << endl;
			exit(1);
		}
	}
	else
	{
		int status = client->sendMessage(update);
		if(status == 0) {
			cout << "Error sending..." << endl;
			exit(1);
		}
	}
}

int NetworkPlayer::receiveMove()
{
	char* msg;
	if (isServer)
		msg = server->receiveMessage();
	else 
		msg = client->receiveMessage();

	cout << "msg recevied: " << msg << endl;
	return atoi(msg);
}

int NetworkPlayer::play(bool valid) 
{
	if(!firstRun) {
		cout << "Not first run" << endl;
		updateOpponent();
	} else {
		cout << "First run" << endl;
		firstRun = false;
	}
	return receiveMove();
}