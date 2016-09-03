#ifndef RandomPlayer_H
#define RandomPlayer_H

#include "Player.h"
#include <random>
#include <memory>
#include <chrono>
#include <functional>

class RandomPlayer: public Player
{
public:
	RandomPlayer(int numRows, int numCols, Board* iboard);
	RandomPlayer(Board* iboard);
	~RandomPlayer();
	virtual int play(bool valid);
	virtual void initialise();
	virtual void setFirst();
	virtual void Exit(bool);

private:
	//Necessary for generating random values
	std::uniform_int_distribution<int> distribution;
	std::default_random_engine generator;
	std::function<int()> dice;
};


#endif // RandomPlayer_H 