#include "MiniMaxPlayer.h"
#include "consts.h"
#include "ColourDef.h"

#include <chrono>
#include <thread>


//Deprecated... Now use as argument for minimax
#ifndef MAX_DEPTH
#define MAX_DEPTH 3
#endif

#define INFINITY 999999

int global_prunes = 0;

MiniMaxPlayer::MiniMaxPlayer(int Cols, int Rows, Board* iBoard, Node* iroot, int iturn) : 
	Player(Cols, Rows, iBoard), Variation(NULL), alloc(false), turnReference(iturn), root(iroot) {}

MiniMaxPlayer::~MiniMaxPlayer() 
{
	//delete root;
	delete[] Variation;
}

using namespace std;

int MiniMaxPlayer::play(bool valid)
{
	Node* test = new Node(global_id++, board->getBoardState(0), (turnReference+1)%2);
	cout << "TURN REF: " << turnReference;
	int depth = 2;
	bool Maximizing = (turnReference==0) ? true : false;
	auto start = chrono::steady_clock::now();
	int utility = AlphaBeta(test, depth, -INFINITY, INFINITY, Maximizing);
	auto end = chrono::steady_clock::now();
	chrono::duration<double> diff = end-start;

	int move0 = test->GetMove();

	int move = Variation[depth]+1;		//Move is column index (1 indexed) not state index
	cout << "\nBest Utility: " << utility << " in " << diff.count() << "s" << endl;
	cout << "Explored " << global_id << " Nodes..." << endl;
	cout << "Move: " << move << endl;
	cout << "Number of pruned: " << global_prunes << endl;

	return move;
	/*
	global_id = 0;
	GameState* state = board->getBoardState(0);
	if (verbose >3)
		cout << "Generating root node" << endl;
	Node* test = new Node(global_id++, state, turnReference);	//Last parameter 1 assuming computer goes 2ND always
	
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	(void) EvalUtil(test);
	std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();

	if (verbose >3)
		cout << "Retrieving possible moves..." << endl;
	Node** possibleMoves = test->getChildren();
	
	int max = -65536;
	int min = 65536;
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
	cout << "Utility: " << ((turnReference==1) ? max : min) << endl;

	//Expects a column i.e. 1-indexed
	return play+1;
	*/
}

void MiniMaxPlayer::initialise() {}

void MiniMaxPlayer::setFirst() {}

void MiniMaxPlayer::Exit(bool) {}

int MiniMaxPlayer::EvalUtil(Node* current)
{
	return 0;
	/*
	if (verbose >3)
		current->print();
	Node** children = current->discoverChildren();
	int numChildren = current->numChild;
	int turn = current->getTurn();

	int retVal = current->computeUtil();
	int depth = current->getDepth();
	//If leaf node OR a winning/losing state OR depth maximum hit
	if (numChildren == 0 || retVal >= 900 || retVal <= -900 || depth >= MAX_DEPTH) {
		//delete current;
		return retVal;
	}
	
	int max = -65536;
	int min = 65536;

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
		*/
}

int MiniMaxPlayer::Minimax(Node* current, int depth, bool MaxPlayer)
{
	if (!alloc) {
		Variation = new int[depth+1]();
		alloc = true;
	}
	bool xWins = current->GetState()->checkWin('X');
	bool oWins = current->GetState()->checkWin('O');
	if (depth == 0 || xWins || oWins)
		return current->ComputeUtil();

	Node** children = current->DiscoverChildren();
	if (MaxPlayer)
	{
		int bestValue = -INFINITY;
		for (int i=0; i<current->GetNumberOfChildren(); i++) {
			children[i]->Move();
			if (verbose>3)
				children[i]->Print();
			int cValue = Minimax(children[i], depth-1, false);
			cValue = DepthNormalise(cValue);
			if (cValue>=bestValue) {
				bestValue = cValue;
				move = children[i]->GetMove();
				if (verbose>3) {
					cout << ANSI_CYAN;
					cout << "At depth: " << depth << " New maximum: " << cValue << " move: " << move+1 << endl;
					cout << ANSI_RESET;
				}
				Variation[depth] = move;	//Wrong for all other than root
			}
			children[i]->UnMove();
			delete children[i];
		}
		return bestValue;
	}
	else
	{
		int bestValue = INFINITY;
		for (int i=0; i<current->GetNumberOfChildren(); i++) {
			children[i]->Move();
			if (verbose>3)
				children[i]->Print();
			int cValue = Minimax(children[i], depth-1, true);
			cValue = DepthNormalise(cValue);
			if (cValue<=bestValue) {
				bestValue = cValue;
				move = children[i]->GetMove();
				if (verbose>3) {
					cout << ANSI_CYAN;
					cout << "At depth: " << depth << " New minimum: " << cValue << " move: " << move+1 << endl;
					cout << ANSI_RESET;
				}
				Variation[depth] = move;	//Wrong for all other than root
			}
			children[i]->UnMove();
			delete children[i];
		}
		return bestValue;
	}
}

int MiniMaxPlayer::DepthNormalise(int value)
{
	if ( value<0 ) {
		value++;
	} else if ( value>0 ) {
		value--;
	}
	return value;
}

int MiniMaxPlayer::AlphaBeta(Node* current, int depth, int alpha, int beta, bool MaxPlayer)
{
	if (!alloc) {
		Variation = new int[depth+1]();
		alloc = true;
	}
	bool xWins = current->GetState()->checkWin('X');
	bool oWins = current->GetState()->checkWin('O');
	if (depth == 0 || xWins || oWins)
		return current->ComputeUtil();
	
	int bestValue;
	Node** children = current->DiscoverChildren();
	if (MaxPlayer)
	{
		bestValue = -INFINITY;
		for (int i=0; i<current->GetNumberOfChildren(); i++) {
			children[i]->Move();
			if (verbose>3)
				children[i]->Print();
			int cValue = AlphaBeta(children[i], depth-1, alpha, beta, false);
			cValue = DepthNormalise(cValue);
			if (cValue>=bestValue) {
				bestValue = cValue;
				move = children[i]->GetMove();
				if (verbose>3) {
					cout << ANSI_CYAN;
					cout << "At depth: " << depth << " New maximum: " << cValue << " move: " << move+1 << endl;
					cout << ANSI_RESET;
				}
				Variation[depth] = move;	//Wrong for all other than root
			}
			children[i]->UnMove();
			alpha = (alpha >= bestValue) ? alpha : bestValue;
			bestValue = alpha;
			if (beta <= alpha) {
				global_prunes++;
				break;	
			}
		}
	}
	else
	{
		bestValue = INFINITY;
		for (int i=0; i<current->GetNumberOfChildren(); i++) {
			children[i]->Move();
			if (verbose>3)
				children[i]->Print();
			int cValue = AlphaBeta(children[i], depth-1, alpha, beta, true);
			cValue = DepthNormalise(cValue);
			if (cValue<=bestValue) {
				bestValue = cValue;
				move = children[i]->GetMove();
				if (verbose>3) {
					cout << ANSI_CYAN;
					cout << "At depth: " << depth << " New minimum: " << cValue << " move: " << move+1 << endl;
					cout << ANSI_RESET;
				}
				Variation[depth] = move;	//Wrong for all other than root
			}
			children[i]->UnMove();
			beta = (beta <= bestValue) ? beta : bestValue;
			bestValue = beta;
			if (beta <= alpha) {
				global_prunes++;
				break;
			}
		}
	}
	for (int i=0; i<current->GetNumberOfChildren(); i++) {
		delete children[i];
	}
	return bestValue;
}

int* MiniMaxPlayer::GetVariation()
{
	return Variation;
}

void MiniMaxPlayer::PrintVariation(bool Maximizing)
{
	cout << "Outputting Optimal Variation...: " << endl;
	
	bool FlipFlop = Maximizing;

	//bCpy = COPY OF board...

	for (int i=depth; i>=0; i--) {
		board->update_cell(Variation[i], ((FlipFlop) ? 'X' :'O') );
		if (FlipFlop) {
			cout << "Depth: [" << depth-i << "]: Max Player Has Col: " << Variation[i]+1 << endl; 
		} else {
			cout << "Depth: [" << depth-i << "]: Min Player Has Col: " << Variation[i]+1 << endl; 
		}
		board->print();
		this_thread::sleep_for(1s);
		FlipFlop = !FlipFlop;

		cout << "\n\n" << endl;
	}

	//Free bCpy
}