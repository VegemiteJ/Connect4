#include "GameState.h"
#include "Node.h"
#include "MiniMaxPlayer.h"
#include "board.h"
#include "consts.h"
#include "ColourDef.h"
#include "Params.h"
#include "PrintConsole.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include <thread>


int verbose = 4;

using namespace std;


int main(int argc, const char** argv)
{
	Params* settings = new Params();

	settings->ParseParams(argc, argv);

	cout << "Player1: " << settings->p1 << endl;
	cout << "Player1 Param: " << settings->aiParams1 << endl;
	cout << "Player1 time: " << settings->idTime1 << endl;
	cout << "Player1 maxDepth: " << settings->itrDepth1 << endl;
	cout << "Player1 Node: " << settings->heuristic1 << endl;
	cout << "Player1 randSwaps: " << settings->randSwaps1 << endl;

	cout << "Player2: " << settings->p2 << endl;
	cout << "Player2 Param: " << settings->aiParams2 << endl;
	cout << "Player2 time: " << settings->idTime2 << endl;
	cout << "Player2 maxDepth: " << settings->itrDepth2 << endl;
	cout << "Player2 Node: " << settings->heuristic2 << endl;
	cout << "Player2 randSwaps: " << settings->randSwaps2 << endl;

	cout << "Initial board state: " << settings->bs << endl;
	cout << "Output File: " << settings->of << endl;
	verbose = settings->verbosity;
	cout << "Verbose level: " << verbose << endl;
	//settings->ParseParams(argc, argv);

	/*
	Board* board = new Board(6,7);
	
	/*
	board->update_cell(0,'X');
	board->update_cell(0,'X');
	board->update_cell(0,'X');
	board->update_cell(1,'O');
	board->update_cell(2,'O');
	board->update_cell(3,'O');
	board->update_cell(1,'O');
	board->update_cell(2,'O');
	board->update_cell(3,'O');
	
	
	MiniMaxPlayer* testPlayer = new MiniMaxPlayer(7, 6, board, NULL, 0, 15, 6, 2, 10000, 16);

	testPlayer->PrintSettings();
	
	*/
	/*
	GameState* state = board->getBoardState(0);
	Node* initial = new Node(global_id, state, 0);
	board->print();
	*/
	/*
	cout << "-1,-1: " << initial->DetermineDirection(-1,-1) << endl;
	cout << "-1,0: " << initial->DetermineDirection(-1,0) << endl;
	cout << "-1,1: " << initial->DetermineDirection(-1,1) << endl;
	cout << "0,-1: " << initial->DetermineDirection(0,-1) << endl;
	cout << "0,1: " << initial->DetermineDirection(0,1) << endl;
	cout << "1,-1: " << initial->DetermineDirection(1,-1) << endl;
	cout << "1,0: " << initial->DetermineDirection(1,0) << endl;
	cout << "1,1: " << initial->DetermineDirection(1,1) << endl;
	*/

	
	
	/*
	int* Variation = testPlayer->GetVariation();
	bool FlipFlop = Maximizing;
	for (int i=depth; i>=0; i--) {
		board->update_cell(Variation[i], ((FlipFlop) ? 'X' :'O') );
		if (FlipFlop) {
			cout << "Depth: [" << depth-i << "]: Max Player Has Col: " << Variation[i]+1 << endl; 
		} else {
			cout << "Depth: [" << depth-i << "]: Min Player Has Col: " << Variation[i]+1 << endl; 
		}
		board->print();
		this_thread::sleep_for(6s);
		FlipFlop = !FlipFlop;

		cout << "\n\n" << endl;
	}
	*/
}