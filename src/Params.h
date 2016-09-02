#ifndef PARAMS_H
#define PARAMS_H

#include "Player.h"

//Makes a container
class Params
{
private:
	int argc;
	const char** argv;

	void InputSuccess();
	void ParsePlayer(std::string);
public:

	//Construct container class
	Params();
	void ParseParams(int argc, const char** argv);

	//Game specific setup
	bool networkGame;
	bool isServer;
	bool seenFirstPlayer;
	bool seenPlayers;
	string p1;
	string p2;

	//Node specific
	int heuristic1;	
	int randSwaps1;
	int heuristic2;	
	int randSwaps2;
				
	//AI player specific				
	int aiParams1;
	int idTime1;
	int itrDepth1;
	
	int aiParams2;
	int idTime2;
	int itrDepth2;

	string bs;
	string of;
	int verbosity;
};


#endif