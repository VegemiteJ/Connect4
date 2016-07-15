#include "Node.h"
#include "consts.h"
#include "ColourDef.h"
#include <iostream>

int global_id = 0;

using namespace std;

Node::Node() {}

Node::Node(int iid, GameState* iinitial, int iturn) :
	id(iid), state(iinitial), depth(0), numChild(-1), turn(iturn) {}

Node::Node(int iid, Node* iparent, int idepth, int icol) :
	id(iid), parent(iparent), depth(idepth), turn( (iparent->getTurn()+1)%2 )
{
	//New Board State
	if (verbose >3)
		cout << "New Node off previous with new turn: " << turn << endl;
	state = new GameState(iparent->getState(), icol, turn);
}

Node::~Node() 
{
	//delete[] myChildren;
	/*delete util;
	delete state;*/
}

void Node::print() 
{
	cout << "ID: " << ANSI_PURPLE << id << ANSI_RESET << " Number of Children: " << ANSI_PURPLE << numChild << ANSI_RESET;
	cout << " Turn: " << ANSI_PURPLE << turn << ANSI_RESET << " Depth: " << ANSI_PURPLE << depth << ANSI_RESET << endl;
	state->print();
	cout << "Last Move: " << state->LastMoveRow << " " << state->LastMoveCol << endl;
	cout << "X Win?: " << state->checkWin('X') << ", O Win?: " << state->checkWin('O') << endl;
}

int Node::getTurn()
{
	return turn;
}

GameState* Node::getState()
{
	return state;
}

Node** Node::discoverChildren()
{
	if (verbose >3)
		cout << "Discover Children..." << endl;
	if (verbose >3)
		cout << "Num Rows: " << state->numRows << "Num Cols: " << state->numCols << endl;
	numChild = 0;
	int children[state->numCols];
	//Discover number of children
	for (int i=0; i<state->numCols; i++) {
		if (state->checkValidMove(i)){
			children[numChild] = i;
			numChild++;
			if (verbose >3)
				cout << "Column: " << i << " " << children[numChild-1];
		}
	}

	if (verbose >3)
		cout << "NumChild: " << numChild << endl;
	if (numChild != 0) {
		myChildren = new Node*[numChild];
		util = new int[numChild]();
	} else {
		myChildren = NULL;
		util = NULL;
	}
	

	for (int i = 0; i<numChild; ++i){
		if (state->checkValidMove(children[i]))
		{
			if (verbose >3)
				cout << "Making node: " << i << endl;
			myChildren[i] = new Node(global_id++, this, depth+1, children[i]);
		}
	}

	return myChildren;
}

int Node::computeUtil()
{
	char thisTurnToken = (turn==0) ? 'X' : 'O';
	
	char currentCheckToken1 = 'X';
	char currentCheckToken2 = 'O';

	if (verbose >3)
		cout << "thisTurnToken = " << thisTurnToken << endl;
	if (verbose >3)
		cout << "Stat1: " << state->checkWin(currentCheckToken1) << " " << (currentCheckToken1==thisTurnToken) << endl;
	if (verbose >3)
		cout << "Stat2: " << state->checkWin(currentCheckToken2) << " " << (currentCheckToken2==thisTurnToken) << endl;
	// If this turn has won, return max util
	if (state->checkWin(currentCheckToken1) && currentCheckToken1 == thisTurnToken)
	{
		if (verbose >3)
			cout << "Player X Appears to have won, returning max utility" << endl;
		int base = 900;
		int retVal = base + (100-depth);
		return retVal;
	}
	else if (state->checkWin(currentCheckToken2) && currentCheckToken2 == thisTurnToken)
	{
		if (verbose >3)
			cout << "Player O Appears to have won, returning min utility" << endl;
		int base = -900;
		int retVal = base - (100-depth);
		return retVal;
	}

	//Neither player Won
	return 0;
}

void Node::setUtil(int i, int value)
{
	util[i] = value;
}

int Node::getDepth()
{
	return depth;
}

int* Node::getUtil()
{
	return util;
}

Node** Node::getChildren()
{
	return myChildren;
}