#include "GameState.h"
#include "Node.h"
#include "board.h"
#include <iostream>

using namespace std;

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

	Node* test = new Node(0, state, 1);
	test->print();
	
	cout << "\n\nPrinting children..." << endl;
	Node** testChild = test->discoverChildren();
	cout << "Number Children: " << test->numChild << endl;

	for (int i=0; i< test->numChild; i++) {
		cout << "Node " << i << ": " << endl;
		testChild[i]->print();
	}
}