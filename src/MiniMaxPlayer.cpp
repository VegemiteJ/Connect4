#include "MiniMaxPlayer.h"
#include "consts.h"
#include "ColourDef.h"

#include <chrono>

#ifndef MAX_DEPTH
#define MAX_DEPTH 5
#endif

MiniMaxPlayer::MiniMaxPlayer(int Cols, int Rows, Board* iBoard, Node* iroot, int iturn) : 
	Player(Cols, Rows, iBoard), root(iroot), turnReference(iturn) {}

MiniMaxPlayer::~MiniMaxPlayer() 
{
	delete root;
}

int MiniMaxPlayer::play(bool valid)
{
	global_id = 0;
	GameState* state = board->getBoardState(0);
	if (verbose >3)
		cout << "Generating root node" << endl;
	Node* test = new Node(global_id++, state, turnReference);	//Last parameter 1 assuming computer goes 2ND always
	
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	int optimalPlay = EvalUtil(test);
	std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();

	if (verbose >3)
		cout << "Retrieving possible moves..." << endl;
	Node** possibleMoves = test->getChildren();
	
	int max = -999;
	int min = 999;
	int play = possibleMoves[0]->getState()->LastMoveCol;
	int* utilVals = test->getUtil();
	//Determine  move to make:
	cout << "\n\nChoosing Move..." << endl;
	
		for (int i=0; i<test->numChild; i++)
		{
			if (turnReference==1) {
				if (utilVals[i] >= max) {
					max = utilVals[i];
					play = possibleMoves[i]->getState()->LastMoveCol;
					if (verbose >3)
						cout << "New Maximum Move -- Util: " << max << " -- Move: " << play << endl;
				}
			} else {		//Turn reference = 0
				if (utilVals[i] <= min) {
					min = utilVals[i];
					play = possibleMoves[i]->getState()->LastMoveCol;
					if (verbose >3)
						cout << "New Maximum Move -- Util: " << min << " -- Move: " << play << endl;
				}
			}
			//Purge the search tree
			cout << "Deleting Search Tree..." << endl;
			possibleMoves[i]->deleteTree();
		}

	cout << "Chose move: " << play+1 << " after " << global_id << " state evaluations in ";
	cout << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000000.0 << " seconds" << endl;

	//Expects a column i.e. 1-indexed
	return play+1;
}

void MiniMaxPlayer::initialise() {}

void MiniMaxPlayer::setFirst() {}

void MiniMaxPlayer::Exit(bool) {}

int MiniMaxPlayer::EvalUtil(Node* current)
{
	if (verbose >3)
		current->print();
	Node** children = current->discoverChildren();
	int numChildren = current->numChild;
	int turn = current->getTurn();

	int retVal = current->computeUtil();
	int depth = current->getDepth();
	//If leaf node OR a winning/losing state OR depth maximum hit
	if (numChildren == 0 || retVal > 800 || retVal < -800 || depth >= MAX_DEPTH) {
		//delete current;
		return retVal;
	}
	
	int max = -999;
	int min = 999;

	//For each child, detemine util
	for (int i=0; i<numChildren; i++) {
		if (verbose >3)
			cout << "Child " << i << " Utility: " << ANSI_CYAN << children[i]->computeUtil() << ANSI_RESET << endl;
		int childVal = EvalUtil(children[i]);
		current->setUtil(i, childVal);
		if (verbose >3)
			cout << "Child returns: " << ANSI_CYAN << childVal << ANSI_RESET << endl;
		if (turn == 1) {	//If player X
			max = (childVal > max) ? childVal : max;
		} else {
			min = (childVal < min) ? childVal : min;
		}
		//delete children[i];
	}
	//delete children;
	if (verbose >3) {
		if (turn==1)
			cout << "Choosing Maximum: " << ANSI_YELLOW << max << ANSI_RESET << endl;
		else
			cout << "Choosing Minimum: " << ANSI_YELLOW << min << ANSI_RESET << endl;
	}
	//Minimax turn determination
	if (turn == 1)
		return max;
	else
		return min;
}