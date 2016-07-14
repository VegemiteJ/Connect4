#include "GameState.h"
#include "Node.h"
#include "MiniMaxPlayer.h"
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

	cout << "Now passing to GameState" << endl;
	GameState* state = board->getBoardState(0);

	cout << "Generating root node" << endl;
	Node* test = new Node(global_id++, state, 1);
	test->print();

	MiniMaxPlayer* testPlayer = new MiniMaxPlayer(test);
	cout << "Final Value: " << testPlayer->EvalUtil(test) << endl;
	
}