#ifndef MiniMaxPlayer_H
#define MiniMaxPlayer_H

#include "Board.h"
#include "Player.h"
#include "Node.h"

class MiniMaxPlayer : public Player
{
public:
	//Parameters: Number of Rows, Number of Cols, Board, Initial Search node (deprecated)
	//	Turn (0 if p1, 1 if p2), Algorithm to use: 0 for AB, 1 for MM
	MiniMaxPlayer(int numRows, int numCols, Board* iBoard, Node* root, int iturn, int iAlg);
	~MiniMaxPlayer();

	//Returns column to place move in. If previous move was invalid, param valid set to true
	virtual int play(bool valid);

	//Unused Player-Inherited functions
	virtual void initialise();
	virtual void setFirst();
	virtual void Exit(bool);

	//Returns best utility.
	//Params: Current execution Node, current depth (initialised to max depth (e.g. 9))
	//	Maximising player : True if me, False if I am minimising player 
	int Minimax(Node* current, int depth, bool MaxPlayer);

	//Returns best utility.
	//Params: Current execution Node, current depth (initialised to max depth (e.g. 9))
	//	Maximising player : True if me, False if I am minimising player
	int AlphaBeta(Node* current, int depth, int alpha, int beta, bool MaxPlayer);

	//Return pointer to principle variation (Incorrect at the moment.
	//	Only ReturnArr[0] has the correct valid move)
	int* GetVariation();

	//Print the Principle variation
	void PrintVariation(bool Maximising);

private:
	MiniMaxPlayer();

	//Return the best possible utility.
	//	Runs while within computational budget
	int IterativeDeepen(int milliseconds);

	//Scale the absolute value of value upwards
	//	Returns modified value
	//	e.g. Value 950 becomes 951, -950 becomes -951
	int DepthNormalise(int value);
	
	//Returns the best move from Minimax
	int GetMMPlay();

	//Returns the best move from AlphaBeta
	int GetABPlay();

	//The array holding prinicple variation
	int* Variation;

	//True if variation set
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