#include "RandomPlayer.h"
#include <iostream>
#include <cstdlib>

using namespace std;

RandomPlayer::RandomPlayer(int numRows, int numCols, Board* iboard)
	: Player(numRows, numCols, iboard) 
{
	id = 2;
	distribution = uniform_int_distribution<int>(1,numCols);
	generator.seed(chrono::system_clock::now().time_since_epoch().count());
	dice = bind(distribution, generator);
}

RandomPlayer::RandomPlayer(Board* iboard)
	: Player(iboard) 
{
	id = 2;
	distribution = uniform_int_distribution<int>(1,iboard->GetCol());
	generator.seed(chrono::system_clock::now().time_since_epoch().count());
	dice = bind(distribution, generator);
}

RandomPlayer::~RandomPlayer() {}

void RandomPlayer::initialise() {}
void RandomPlayer::setFirst() {}
void RandomPlayer::Exit(bool val) {}

int RandomPlayer::play(bool valid) 
{
	int tentatitve = dice();
	while(!board->checkValidMove(tentatitve-1))	//While that column is full gen. more moves
	{
		tentatitve = dice();
	}
	return tentatitve;
}