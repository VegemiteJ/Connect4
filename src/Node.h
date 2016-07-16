#ifndef NODE_H
#define NODE_H

#include "GameState.h"

class Node
{
public:
	Node(int id, GameState* initial, int iturn);

	//global id, parent of this node in tree
	//column -- 0-indexed
	Node(int id, Node* parent, int col);
	~Node();
	void deleteTree();

	void print();

	int numChild;
	GameState* getState();
	int getTurn();
	int getDepth();
	int* getUtil();
	void setUtil(int i, int value);
	Node** getChildren();

	Node** discoverChildren();
	int computeUtil();

private:
	Node();
	
	//Bitmask of what items are allocated
	//           LSB
	//   X--X--X--X    #Form
	//   1--0--0--0    #util
	//   0--1--0--0    #myChildren
	//   0--0--1--0    #parent
	//   0--0--0--1    #state
	//   0--0--0--0    #None
	// e.g. if part of search tree, allocation will be 1-1-1-1
	//   Used for intelligent destructor
	int allocated;

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