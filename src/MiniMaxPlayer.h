#ifndef MiniMaxPlayer_H
#define MiniMaxPlayer_H

#include "Board.h"
#include "Player.h"
#include "Node.h"

class MiniMaxPlayer : public Player
{
public:
	MiniMaxPlayer(int Cols, int Rows, Board* iBoard, Node* root, int iturn);
	~MiniMaxPlayer();
	virtual int play(bool valid);
	virtual void initialise();
	virtual void setFirst();
	virtual void Exit(bool);

	int EvalUtil(Node* current);

private:
	int turnReference;
	MiniMaxPlayer();
	Node* root;
};


#endif // MiniMaxPlayer_H 