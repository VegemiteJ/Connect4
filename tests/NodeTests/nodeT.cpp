#include "Board.h"
#include "GameState.h"
#include "Node.h"
#include "consts.h"
#include "ColourDef.h"
#include <iostream>

int verbose = 4;

using namespace std;

int main(int argc, char** argv)
{
	Board* board = new Board(4,4);
	board->update_cell(0,'O');
	board->update_cell(1,'O');
	board->update_cell(0,'X');
	board->update_cell(0,'X');
	board->update_cell(1,'X');
	board->update_cell(1,'X');

	cout << "Now passing to GameState" << endl;
	GameState* state = board->getBoardState(0);

	Node* test = new Node(global_id++, state, 1);
	test->print();
	Node* test1 = new Node(global_id++, test, 2);
	test1->print();

	//Delete children
	Node** children = test1->discoverChildren();
	test1->deleteTree();
	delete test1;
	delete test;
}