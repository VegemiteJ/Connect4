#include "GameState.h"
#include "Node.h"
#include "MiniMaxPlayer.h"
#include "board.h"
#include "consts.h"
#include "ColourDef.h"
#include <iostream>
#include <thread>

int verbose = 0;

using namespace std;

int main(int argc, char** argv)
{
	Board* board = new Board(6,7);

	board->update_cell(4,'X');
	board->update_cell(4,'X');
	board->update_cell(4,'X');
	board->update_cell(4,'O');
	board->update_cell(4,'X');
	cout << "Now passing to GameState" << endl;
	GameState* state = board->getBoardState(0);

	cout << "Generating root node" << endl;
	Node* test = new Node(global_id++, state, 0);
	test->Print();

	int depth = 10;
	bool Maximizing = false;
	MiniMaxPlayer* testPlayer = new MiniMaxPlayer(4, 4, board, test, 0);
	
	auto start = chrono::steady_clock::now();
	int utility = testPlayer->Minimax(test, depth, Maximizing);
	auto end = chrono::steady_clock::now();
	chrono::duration<double> diff = end-start;

	int move = testPlayer->move;
	cout << "\nBest Utility: " << utility << " in " << diff.count() << "s" << endl;
	cout << "Explored " << global_id << " Nodes..." << endl;
	cout << "Outputting Optimal Variation...: " << endl;
	
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
		this_thread::sleep_for(1s);
		FlipFlop = !FlipFlop;

		cout << "\n\n" << endl;
	}
}