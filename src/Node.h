#ifndef NODE_H
#define NODE_H

#include "GameState.h"

class Node
{
public:
	Node(int id, GameState* initial, int iturn);
	Node(int id, Node* parent, int depth, int col);
	~Node();

	void print();
	GameState* getState();
	int getTurn();

	Node** discoverChildren();
	int numChild;

private:
	Node();
	
	int id;

	int* util;
	int turn;		//0 for X, 1 for O

	Node** myChildren;
	Node* parent;			//Usually blank

	int depth;

    //Tuple of [row, col] location to evaluation
	//int state->LastMoveRow;
	//int state->LastMoveCol;

	//Board state of me
	GameState* state;
	
};

#endif