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

	int Minimax(Node* current, int depth, bool MaxPlayer);

	int move;
private:
	MiniMaxPlayer();

	int DepthNormalise(int value);

	int turnReference;
	Node* root;
};


#endif // MiniMaxPlayer_H 