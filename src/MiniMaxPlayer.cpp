#include "MiniMaxPlayer.h"
#include "Consts.h"
#include "ColourDef.h"

#include <chrono>
#include <thread>
#include <random>
#include <functional>

#define INF 999999

int global_prunes = 0;

//iAlg is 0 -> Alpha beta else minimax
MiniMaxPlayer::MiniMaxPlayer(int Cols, int Rows, Board* iBoard, Node* iroot, int iturn, int iAlg) : 
	Player(Cols, Rows, iBoard), Variation(NULL), alloc(false), utility(0), algRef(iAlg), turnReference(iturn), root(iroot)
	{
		startDepth = 5;
	}

MiniMaxPlayer::~MiniMaxPlayer() 
{
	//delete root;
	delete[] Variation;
}

using namespace std;

int MiniMaxPlayer::play(bool valid)
{
	global_prunes = 0;
	global_id = 0;
	int ret = IterativeDeepen(24000);
	if (verbose == 0) {
		cout << "\nUtility Estimate: " << utility << endl;
		cout << "Reached Depth: " << startDepth << endl;
	}
	return ret;

}

int MiniMaxPlayer::IterativeDeepen(int milliseconds)
{
	startDepth = 5;
	//Set start time
	auto start = chrono::steady_clock::now();
	auto startTime = chrono::steady_clock::now();
	
	//Run default depth search
	int move;
	if (algRef == 0)
		move = GetABPlay();
	else
		move = GetMMPlay();

	auto runTime = chrono::steady_clock::now();
	double runLength = chrono::duration_cast<chrono::milliseconds>(runTime-startTime).count();
	double difference = chrono::duration_cast<chrono::milliseconds>(runTime-start).count();
	if (verbose>1)
		cout << "Total Time so far: " << difference << "ms" << endl;
	
	int* size = board->getSize();
	int depthPossible = size[0]*size[1] - board->numMoves;
	delete[] size;

	if (verbose > 1)
		cout << "Number of Possible Moves: " << depthPossible << endl;


	//While current time - start time < 10 seconds continue running searches with depth+1
	//	I.e while within computational budget. Very rough estimation is 6.0*prevRunTime < timeRemaining
	while( 6.0*runLength < (milliseconds-difference) && startDepth <= depthPossible )
	{
		startDepth++;
		startTime = chrono::steady_clock::now();
		
		if (algRef == 0)
			move = GetABPlay();
		else
			move = GetMMPlay();

		runTime = chrono::steady_clock::now();

		runLength = chrono::duration_cast<chrono::milliseconds>(runTime-startTime).count();
		difference = chrono::duration_cast<chrono::milliseconds>(runTime-start).count();
		if (verbose>1) {
			cout << "Total Time so far: " << difference << "ms" << endl;
		}
	}
	return move;
}

int MiniMaxPlayer::GetABPlay()
{
	if (verbose > 1)
		cout << "\n\nAB Searching to depth: " << startDepth << endl;
	Node* test = new Node(global_id++, board->getBoardState(0), (turnReference+1)%2);
	if (verbose>3)
		cout << "TURN REF: " << turnReference << endl;

	bool Maximizing = (turnReference==0) ? true : false;
	auto start = chrono::steady_clock::now();
	utility = AlphaBeta(test, startDepth, -INF, INF, Maximizing);
	auto end = chrono::steady_clock::now();
	chrono::duration<double> diff = end-start;

	int move = Variation[startDepth]+1;		//Move is column index (1 indexed) not state index

	if (verbose>1) {
		cout << "Depth: " << startDepth << endl;
		cout << "Best Utility: " << utility << " in " << diff.count() << "s" << endl;
		cout << "Explored " << global_id << " Nodes..." << endl;
		cout << "Number of pruned: " << global_prunes << endl;
		if (verbose>3) {
			cout << "Initial Turn: " << turnReference << " Maximizing: "  << Maximizing << endl;
			cout << "Move: " << move << endl;
		}
	}

	return move;
}

int MiniMaxPlayer::GetMMPlay()
{
	if (verbose > 1)
		cout << "\n\nMM Searching to depth: " << startDepth << endl;
	Node* test = new Node(global_id++, board->getBoardState(0), (turnReference+1)%2);
	if (verbose>3)
		cout << "TURN REF: " << turnReference << endl;

	bool Maximizing = (turnReference==0) ? true : false;
	auto start = chrono::steady_clock::now();
	int utility = Minimax(test, startDepth, Maximizing);
	auto end = chrono::steady_clock::now();
	chrono::duration<double> diff = end-start;

	int move = Variation[startDepth]+1;		//Move is column index (1 indexed) not state index

	if (verbose>1) {
		cout << "Best Utility: " << utility << " in " << diff.count() << "s" << endl;
		cout << "Explored " << global_id << " Nodes..." << endl;
		cout << "Number of pruned: " << global_prunes << endl;
		if (verbose>3) {
			cout << "Initial Turn: " << turnReference << " Maximizing: "  << Maximizing << endl;
			cout << "Move: " << move << endl;
		}
	}
	return move;
}

void MiniMaxPlayer::initialise() {}

void MiniMaxPlayer::setFirst() {}

void MiniMaxPlayer::Exit(bool) {}

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
		int bestValue = -INF;
		for (int i=0; i<current->GetNumberOfChildren(); i++) {
			children[i]->Move();
			if (verbose>3)
				children[i]->Print();
			int cValue = Minimax(children[i], depth-1, false);
			cValue = DepthNormalise(cValue);
			if (cValue>bestValue) {
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
		int bestValue = INF;
		for (int i=0; i<current->GetNumberOfChildren(); i++) {
			children[i]->Move();
			if (verbose>3)
				children[i]->Print();
			int cValue = Minimax(children[i], depth-1, true);
			cValue = DepthNormalise(cValue);
			if (cValue<bestValue) {
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
	if (verbose>3) {
		cout << "Depth: " << depth << endl;
		cout << "Alpha: " << alpha << " Beta: " << beta << endl;
	}
	if (!alloc) {
		Variation = new int[depth+1]();
		alloc = true;
	}
	bool xWins = current->GetState()->checkWin('X');
	bool oWins = current->GetState()->checkWin('O');
	if (depth == 0 || xWins || oWins)
		return current->ComputeUtil();

	int cValue;
	int bestValue;
	Node** children = current->DiscoverChildren();
	if (MaxPlayer)
	{
		if (verbose>3)
			cout << ANSI_RED << "IsMax" << ANSI_RESET << endl;
		bestValue = -INF;
		for (int i=0; i<current->GetNumberOfChildren(); i++) {
			children[i]->Move();
			if (verbose>3)
				children[i]->Print();
			cValue = AlphaBeta(children[i], depth-1, alpha, beta, false);
			cValue = DepthNormalise(cValue);
			if (cValue>bestValue) {
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
			if (beta <= alpha) {
				global_prunes++;
				break;	
			}
		}
	}
	else
	{
		if (verbose>3)
			cout << ANSI_RED << "IsNotMax" << ANSI_RESET << endl;
		bestValue = INF;
		for (int i=0; i<current->GetNumberOfChildren(); i++) {
			children[i]->Move();
			if (verbose>3)
				children[i]->Print();
			cValue = AlphaBeta(children[i], depth-1, alpha, beta, true);
			cValue = DepthNormalise(cValue);
			if (cValue<bestValue) {
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
	//Complicated
}