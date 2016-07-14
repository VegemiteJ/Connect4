#include "GameState.h"
#include "Node.h"
#include "board.h"
#include "consts.h"
#include "ColourDef.h"
#include <iostream>

using namespace std;

int global_id = 0;

int main(int argc, char** argv)
{
	Board* board = new Board(4,4);
	board->print();
	board->update_cell(0,'O');
	board->update_cell(1,'O');
	board->update_cell(2,'O');
	board->update_cell(0,'X');
	board->update_cell(0,'X');
	board->update_cell(0,'O');
	board->update_cell(1,'X');
	board->update_cell(1,'X');
	board->update_cell(1,'O');
	board->print();

	cout << "Now passing to GameState" << endl;
	GameState* state = board->getBoardState(0);

	Node* test = new Node(global_id++, state, 1);
	test->print();
	
	cout << "\n\nPrinting children..." << endl;
	Node** testChild = test->discoverChildren();
	cout << "Number Children: " << test->numChild << endl;

	for (int i=0; i< test->numChild; i++) {
		testChild[i]->print();
		cout << "Util: " << ANSI_CYAN << testChild[i]->computeUtil() << ANSI_RESET << endl;
		
		Node** testChild1 = testChild[i]->discoverChildren();
		cout << "Number Children: " << testChild[i]->numChild << endl;
		for (int j=0; j<testChild[i]->numChild; j++) {
			testChild1[j]->print();
			cout << "Util: " << ANSI_CYAN << testChild1[j]->computeUtil() << ANSI_RESET << endl;
		}
	}
}