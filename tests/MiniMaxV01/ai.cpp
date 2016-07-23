#include "GameState.h"
#include "Node.h"
#include "MiniMaxPlayer.h"
#include "board.h"
#include "consts.h"
#include "ColourDef.h"
#include <iostream>

int verbose = 0;

using namespace std;

int main(int argc, char** argv)
{
	Board* board = new Board(6,7);

	board->update_cell(4,'X');
	board->update_cell(4,'X');
	board->update_cell(4,'X');

	cout << "Now passing to GameState" << endl;
	GameState* state = board->getBoardState(0);

	cout << "Generating root node" << endl;
	Node* test = new Node(global_id++, state, 1);
	test->Print();

	MiniMaxPlayer* testPlayer = new MiniMaxPlayer(4, 4, board, test, 0);
	int utility = testPlayer->Minimax(test, 2, false);
	int move = testPlayer->move;
	cout << "\nBest Utility: " << utility << endl;
	cout << "Best Move: " << move << endl;
}