#include "Board.h"
#include "GameState.h"
#include "Node.h"
#include "consts.h"
#include "ColourDef.h"
#include "PrintConsole.h"
#include <iostream>

int verbose = 5;

using namespace std;

int main(int argc, char** argv)
{
	Board* board = new Board(6,9);
	board->update_cell(0,'X');
	board->update_cell(0,'X');
	board->update_cell(0,'X');

	cout << "Now passing to GameState" << endl;
	GameState* state = board->getBoardState(0);

	Node* initial = new Node(global_id, state, 0, 15, 8);
	initial->Print();

	PrintConsole("\nChild Expansion...\n", 3);
	Node** child = initial->DiscoverChildren();

	/*
	cout << "\n\n\n\n";
	for (int i=0; i<initial->GetNumberOfChildren(); i++) {
		child[i]->Move();
		child[i]->Print();
		cout << "Utility: " << ANSI_PURPLE << child[i]->ComputeUtil() << ANSI_RESET << endl;
		child[i]->UnMove();
		delete child[i];
	}
	*/
}