#include "Node.h"

Node::Node()
{

}

Node::Node(Node* iparent, GameState* iprev, int idepth, int icol, int iturn) :
	parent(iparent), depth(idepth), col(icol), turn(iturn)
{
	//New Board State
	board_GS = new GameState(iprev, col, turn);
}

Node::~Node() {}

void Node::printNode() {}