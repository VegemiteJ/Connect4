#include "Node.h"
#include "consts.h"
#include "ColourDef.h"
#include <iostream>

using namespace std;

Node::Node() {}

Node::Node(int iid, GameState* iinitial, int iturn) :
	id(iid), state(iinitial), depth(0), numChild(-1), turn(iturn) {}

Node::Node(int iid, Node* iparent, int idepth, int icol) :
	id(iid), parent(iparent), depth(idepth), turn( (iparent->getTurn()+1)%2 )
{
	//New Board State
	cout << "New Node off previous with new turn: " << turn << endl;
	state = new GameState(iparent->getState(), icol, turn);
}

Node::~Node() 
{
	delete[] myChildren;
	delete[] util;
	delete state;
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
	cout << "Discover Children..." << endl;
	cout << "Num Rows: " << state->numRows << "Num Cols: " << state->numCols << endl;
	numChild = 0;
	int children[state->numCols];
	//Discover number of children
	for (int i=0; i<state->numCols; i++) {
		if (state->checkValidMove(i)){
			children[numChild] = i;
			numChild++;
			cout << "Column: " << i << " " << children[numChild-1];
		}
	}

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
			cout << "Making node: " << i << endl;
			myChildren[i] = new Node(global_id++, this, depth+1, children[i]);
		}
	}

	return myChildren;
}

int Node::computeUtil()
{
	int util;
	char thisTurnToken = (turn==0) ? 'X' : 'O';
	
	char currentCheckToken1 = 'X';
	char currentCheckToken2 = 'O';

	cout << "thisTurnToken = " << thisTurnToken << endl;
	cout << "Stat1: " << state->checkWin(currentCheckToken1) << " " << (currentCheckToken1==thisTurnToken) << endl;
	cout << "Stat2: " << state->checkWin(currentCheckToken2) << " " << (currentCheckToken2==thisTurnToken) << endl;
	// If this turn has won, return max util
	if (state->checkWin(currentCheckToken1) && currentCheckToken1 == thisTurnToken)
	{
		cout << "Player X Appears to have won, returning max utility" << endl;
		return 999;
	}
	else if (state->checkWin(currentCheckToken2) && currentCheckToken2 == thisTurnToken)
	{
		cout << "Player O Appears to have won, returning min utility" << endl;
		return -999;
	}

	//Neither player Won
	return 0;
}