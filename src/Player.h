#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
using namespace std;

class Player
{
public:
	Player(char tokenIn);
	void play();
	
private:
	char token;
};


#endif // PLAYER_H 