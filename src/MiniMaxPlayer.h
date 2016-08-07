#ifndef MiniMaxPlayer_H
#define MiniMaxPlayer_H

#include "Board.h"
#include "Player.h"
#include "Node.h"

class MiniMaxPlayer : public Player
{
public:
	//iAlg is 0 -> Alpha beta else minimax
	MiniMaxPlayer(int Cols, int Rows, Board* iBoard, Node* root, int iturn, int iAlg);
	~MiniMaxPlayer();
	virtual int play(bool valid);
	virtual void initialise();
	virtual void setFirst();
	virtual void Exit(bool);

	int Minimax(Node* current, int depth, bool MaxPlayer);
	int AlphaBeta(Node* current, int depth, int alpha, int beta, bool MaxPlayer);

	int* GetVariation();
	void PrintVariation(bool Maximising);

private:
	MiniMaxPlayer();

	int IterativeDeepen(int milliseconds);
	int DepthNormalise(int value);
	int GetMMPlay();
	int GetABPlay();

	int* Variation;
	bool alloc;
	int move;
	int currentMove;
	int utility;

	int algRef;
	int turnReference;
	Node* root;

	int startDepth;
};


#endif // MiniMaxPlayer_H 