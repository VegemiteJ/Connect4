#include "Node.h"
#include <iostream>

using namespace std;

Node::Node() {}

Node::Node(int iid, GameState* iinitial, int iturn) :
	id(iid), state(iinitial), depth(0), numChild(-1), turn(iturn) {}

Node::Node(int iid, Node* iparent, int idepth, int icol) :
	id(iid), parent(iparent), depth(idepth)
{
	//New Board State
	state = new GameState(iparent->getState(), icol, (iparent->getTurn()+1) % 2);
}

Node::~Node() 
{
	delete[] myChildren;
	delete[] util;
	delete[] state;
}

void Node::print() 
{
	cout << "ID: " << id << " Number of Children: " << numChild;
	cout << " Turn: " << turn << " Depth: " << depth << endl;
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
	myChildren = new Node*[numChild];
	util = new int[numChild]();

	for (int i = 0; i<numChild; ++i){
		if (state->checkValidMove(children[i]))
		{
			cout << "Making node: " << i << endl;
			myChildren[i] = new Node(0, this, depth+1, children[i]);
		}
	}

	return myChildren;
}