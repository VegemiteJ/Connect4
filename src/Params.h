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
public:

	//Construct container class
	Params() {}
	void ParseParams(int argc, const char** argv);

	//Game specific setup
	bool networkGame;
	bool isServer;
	Player* p1;
	Player* p2;

	//Node specific
	int heuristic;	
	int randSwaps;
				
	//AI player specific				
	int aiParams;
	int idTime;
	int itrDepth;	
};


#endif