#ifndef MiniMaxPlayer_H
#define MiniMaxPlayer_H

#include "Player.h"
#include "Node.h"

class MiniMaxPlayer// : public Player
{
public:
	MiniMaxPlayer(Node* root);
	~MiniMaxPlayer();
	virtual int play(bool valid);
	virtual void initialise();
	virtual void setFirst();
	virtual void Exit(bool);

	int EvalUtil(Node* current);

private:
	MiniMaxPlayer();

	Node* root;
};


#endif // MiniMaxPlayer_H 