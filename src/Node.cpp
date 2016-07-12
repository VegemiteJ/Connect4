#include "Node.h"

Node::Node()
{

}

Node::Node(Node* iparent, GameState* iprev, int idepth, int irow, int icol, int iturn) :
	parent(iparent), depth(idepth), row(irow), col(icol), turn(iturn)
{
	//Board
	board_GS = new GameState(iprev, row, col, turn);
}

Node::~Node() {}

void Node::printNode() {}