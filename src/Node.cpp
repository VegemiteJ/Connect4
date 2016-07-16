#include "Node.h"
#include "consts.h"
#include "ColourDef.h"
#include <iostream>

int global_id = 0;

using namespace std;

Node::Node() {}

Node::Node(int iid, GameState* iinitial, int iturn) :
	id(iid), state(iinitial), depth(0), numChild(-1), turn(iturn), allocated(0) 
{
	allocated |= 1;
}

Node::Node(int iid, Node* iparent, int icol) :
	id(iid), parent(iparent), depth(iparent->getDepth()+1), turn( (iparent->getTurn()+1)%2 ), allocated(0)
{
	//New Board State
	if (verbose >3)
		cout << "New Node off previous with new turn: " << turn << endl;
	state = new GameState(iparent->getState(), icol, turn);
	allocated |= 1;
	allocated |= 2;
}

Node::~Node() 
{
	if (verbose > 3) {
		cout << ANSI_RED;
		cout << "Called Node Destructor - id: " << id << ANSI_RESET << endl;
		cout << "Allocated: " << ANSI_PURPLE << allocated << ANSI_RESET << endl;
		cout << "BitField: " << endl;
		cout << "X--X--X--X" << endl;
		cout << ANSI_PURPLE;
		cout << ((allocated >> 3) & 1) << "--";		//Util
		cout << ((allocated >> 2) & 1) << "--";		//MyChildren
		cout << ((allocated >> 1) & 1) << "--";		//Parent
		cout << ((allocated >> 0) & 1) << endl;		//State
		cout << ANSI_RESET;
	}

	if ((allocated >> 0) & 1) {
		if (verbose>3)
			cout << "Deleting state..." << endl;
		delete state;
	}
	if ((allocated >> 1) & 1) {
		//Ignore, we don't want to ever delete parent. At this point
		//	May change in future
	}
	if ((allocated >> 2) & 1) {
		//Tree disassemble saved for special destructor deleteTree()
	}
	if ((allocated >> 3) & 1) {
		if (verbose>3)
			cout << "Deleting util..." << endl;
		delete util;
	}

}

void Node::deleteTree()
{
	if (verbose > 3) {
		cout << ANSI_RED;
		cout << "Called Node Full Tree Destructor - id: " << id << ANSI_RESET << endl;
		cout << "Allocated: " << ANSI_PURPLE << allocated << ANSI_RESET << endl;
		cout << "BitField: " << endl;
		cout << "X--X--X--X" << endl;
		cout << ANSI_PURPLE;
		cout << ((allocated >> 3) & 1) << "--";		//Util
		cout << ((allocated >> 2) & 1) << "--";		//MyChildren
		cout << ((allocated >> 1) & 1) << "--";		//Parent
		cout << ((allocated >> 0) & 1) << endl;		//State
		cout << ANSI_RESET;
		cout << "Self wont be fully deleted, only children" << endl;
	}
	if ((allocated >> 1) & 1) {
		//Ignore, we don't want to ever delete parent. At this point
		//	May change in future
	}
	if ((allocated >> 2) & 1) {
		if (verbose>3)
			cout << "Deleting children..." << endl;
		for (int i=0; i<numChild; i++)
		{
			if (verbose>3)
				cout << "Deleting child: " << i << endl;
			myChildren[i]->deleteTree();
		}
		delete myChildren;
		allocated &= 11;
	}
	delete this;
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
		allocated |= 4;
		allocated |= 8;
	} else {
		myChildren = NULL;
		util = NULL;
	}
	

	for (int i = 0; i<numChild; ++i){
		if (state->checkValidMove(children[i]))
		{
			if (verbose >3)
				cout << "Making node: " << i << endl;
			myChildren[i] = new Node(global_id++, this, children[i]);
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