#include "RandomPlayer.h"
#include <iostream>
#include <cstdlib>

using namespace std;

RandomPlayer::RandomPlayer(int numRows, int numCols, Board* iboard)
	: Player(numRows, numCols, iboard) 
{
	id = 2;
	distribution = uniform_int_distribution<int>(1,numCols);
	dice = bind(distribution, generator);
	cout << "Test: " << dice() << dice() << dice() << endl;
}

RandomPlayer::~RandomPlayer() {}

void RandomPlayer::initialise() {}
void RandomPlayer::setFirst() {}
void RandomPlayer::Exit(bool val) {}

int RandomPlayer::play(bool valid) 
{
	int tentatitve = dice();
	while(!board->checkValidMove(tentatitve-1))
	{
		tentatitve = dice();
	}
	return tentatitve;
}