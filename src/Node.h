#ifndef NODE_H
#define NODE_H

#include "GameState.h"

class Node
{
public:
	Node(Node* parent, GameState* prev_board, int depth, int row, int col, int turn);
	~Node();

	void printNode();

private:
	Node();
	
	int numChild;
	int* util;
	int turn;		//0 for X, 1 for O

	Node* myChildren;
	Node* parent;

	int depth;

    //Tuple of [row, col] location to evaluation
	int	row;
	int col;

	//Board state of me
	GameState* board_GS;
	
};

#endif