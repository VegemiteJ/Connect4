#include "GameState.h"
#include "ServerSocketSet.h"
#include "ClientSocketSet.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
	GameState* state = new GameState(4,4);
	GameState* nstate;
	state->print();

	for (int i = -2; i < 6; ++i) {
		cout << "Col: " << i << " Valid move: " << state->checkValidMove(i) << endl;
	}

	for (int col = 0; col < 4; col++) {
		for (int i = 0; i < 6; ++i) {
			cout << "Col: " << col << " Valid move: " << state->checkValidMove(col) << endl;
			nstate = new GameState(state, col, i%2);
			delete state;
			state = nstate;
			state->print();
			cout << "X win?: " << state->checkWin('X') << " O win?: " << state->checkWin('O') << endl;
		}
	}
	
}