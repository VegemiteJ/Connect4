#include "Board.h"
#include "GameState.h"
#include "Node.h"
#include "consts.h"
#include "ColourDef.h"
#include <iostream>

int verbose = 1;

using namespace std;

int main(int argc, char** argv)
{
	Board* board = new Board(4,4);

	cout << "Now passing to GameState" << endl;
	GameState* state = board->getBoardState(0);

	Node* test = new Node(global_id++, state, 1);
	test->print();
	Node* test1 = new Node(global_id++, test, 0);

	//Delete children
	cout << "Running test" << endl;
	while (global_id < 10000000)
	{
		Node** children = test1->discoverChildren();
		test1->deleteTree();
		test1 = new Node(global_id++, test, 0);
	}
}