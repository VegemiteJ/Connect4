#include "MiniMaxPlayer.h"
#include "consts.h"
#include "ColourDef.h"

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

int MiniMaxPlayer::EvalUtil(Node* current)
{
	current->print();
	Node** children = current->discoverChildren();
	int numChildren = current->numChild;
	
	int retVal = current->computeUtil();
	
	if (numChildren == 0 || retVal==999 || retVal ==-999 ) {
		delete current;
		return retVal;
	}
	
	int max = -999;
	int min = 999;

	//For each child, detemine util
	for (int i=0; i<numChildren; i++) {
		cout << "Child " << i << " Utility: " << ANSI_CYAN << children[i]->computeUtil() << ANSI_RESET << endl;
		cout << "Child returns: " << EvalUtil(children[i]) << endl;
		delete children[i];
	}
	delete children;

	return 0;
}