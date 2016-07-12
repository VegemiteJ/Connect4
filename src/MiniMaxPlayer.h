#ifndef MiniMaxPlayer_H
#define MiniMaxPlayer_H

#include "Player.h"
#include <random>
#include <memory>
#include <chrono>
#include <functional>

class MiniMaxPlayer: public Player
{
public:
	MiniMaxPlayer(int numRows, int numCols, Board* iboard);
	~MiniMaxPlayer();
	virtual int play(bool valid);
	virtual void initialise();
	virtual void setFirst();
	virtual void Exit(bool);

private:
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution;
	std::function<int()> dice;
};


#endif // MiniMaxPlayer_H 