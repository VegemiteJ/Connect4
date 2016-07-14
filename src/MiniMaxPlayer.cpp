#include "MiniMaxPlayer.h"
#include "consts.h"
#include "ColourDef.h"

#ifndef MAX_DEPTH
#define MAX_DEPTH 1
#endif

MiniMaxPlayer::MiniMaxPlayer(int Cols, int Rows, Board* iBoard, Node* iroot, int iturn) : 
	Player(Cols, Rows, iBoard), root(iroot), turnReference(iturn) {}

MiniMaxPlayer::~MiniMaxPlayer() 
{
	delete root;
}

int MiniMaxPlayer::play(bool valid)
{
	GameState* state = board->getBoardState(0);
	cout << "Generating root node" << endl;
	Node* test = new Node(global_id++, state, turnReference);	//Last parameter 1 assuming computer goes 2ND always
	
	int optimalPlay = EvalUtil(test);

	cout << "Retrieving possible moves..." << endl;
	Node** possibleMoves = test->getChildren();
	
	int max = -999;
	int min = 999;
	int play = possibleMoves[0]->getState()->LastMoveCol;
	int* utilVals = test->getUtil();
	//Determine  move to make:
	cout << "\n\nChoosing Move" << endl;
	for (int i=0; i<test->numChild; i++)
	{
		if (utilVals[i] >= max) {
			max = utilVals[i];
			play = possibleMoves[i]->getState()->LastMoveCol;
			cout << "New Maximum Move -- Util: " << max << " -- Move: " << play << endl;
		}
	}

	//Expects a column i.e. 1-indexed
	return play+1;
}

void MiniMaxPlayer::initialise() {}

void MiniMaxPlayer::setFirst() {}

void MiniMaxPlayer::Exit(bool) {}

int MiniMaxPlayer::EvalUtil(Node* current)
{
	current->print();
	Node** children = current->discoverChildren();
	int numChildren = current->numChild;
	int turn = current->getTurn();

	int retVal = current->computeUtil();
	int depth = current->getDepth();
	//If leaf node OR a winning/losing state OR depth maximum hit
	if (numChildren == 0 || retVal==999 || retVal ==-999 || depth >= MAX_DEPTH) {
		//delete current;
		return retVal;
	}
	
	int max = -999;
	int min = 999;

	//For each child, detemine util
	for (int i=0; i<numChildren; i++) {
		cout << "Child " << i << " Utility: " << ANSI_CYAN << children[i]->computeUtil() << ANSI_RESET << endl;
		int childVal = EvalUtil(children[i]);
		current->setUtil(i, childVal);
		cout << "Child returns: " << ANSI_CYAN << childVal << ANSI_RESET << endl;
		if (turn == 1) {	//If player X
			max = (childVal > max) ? childVal : max;
		} else {
			min = (childVal < min) ? childVal : min;
		}
		//delete children[i];
	}
	//delete children;
	if (turn==1)
		cout << "Choosing Maximum: " << ANSI_YELLOW << max << ANSI_RESET << endl;
	else
		cout << "Choosing Minimum: " << ANSI_YELLOW << min << ANSI_RESET << endl;

	//Minimax turn determination
	if (turn == 1)
		return max;
	else
		return min;
}