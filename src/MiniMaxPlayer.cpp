#include "MiniMaxPlayer.h"

MiniMaxPlayer::MiniMaxPlayer(Node* iroot) 
{
	root = iroot;
}

MiniMaxPlayer::~MiniMaxPlayer() 
{
	delete root;
}

int MiniMaxPlayer::play(bool valid) {}

void MiniMaxPlayer::initialise() {}

void MiniMaxPlayer::setFirst() {}

void MiniMaxPlayer::Exit(bool) {}

Node* MiniMaxPlayer::EvalUtil(Node* current)
{
	Node** children = current->discoverChildren();
	int numChildren = current->numChild;

	int max = -999;
	//For each child
	for (int i=0; i<numChildren; i++) {

	}


}