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
	
	/*
	board->update_cell(3,'O');
	board->update_cell(3,'O');
	board->update_cell(3,'O');
	*/

	MiniMaxPlayer* testPlayer = new MiniMaxPlayer(7, 6, board, NULL, 0);
	
	cout << "Move returned = " << testPlayer->play(0) << endl;

	board->print();
	
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