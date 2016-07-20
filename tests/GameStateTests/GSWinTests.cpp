// Unit Tests for game state class
// Uses inputs to play game

#include "Game.h"
#include "GameState.h"
#include "Board.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <random>
#include <functional>

int verbose = 0;

using namespace std;

int main(int argc, char** argv)
{

	Board* board = new Board(4,4);
	board->update_cell(0,'X');
	board->update_cell(0,'O');
	board->update_cell(0,'O');
	board->update_cell(0,'O');
	board->update_cell(1,'O');
	board->update_cell(1,'X');
	board->update_cell(1,'O');
	board->update_cell(1,'O');
	board->update_cell(2,'O');
	board->update_cell(2,'O');
	board->update_cell(2,'X');
	board->update_cell(2,'O');
	board->update_cell(3,'O');
	board->update_cell(3,'O');
	board->update_cell(3,'O');
	board->update_cell(3,'X');
	board->print();

	cout << "Now passing to GameState" << endl;
	int* size = board->getSize();
	int nR = size[0];
	int nC = size[1];

	GameState* s1 = new GameState(board->getBoardState(), size[0], size[1]);
	
	cout << "s1 horiz: " << nR << " s1 vert: " << nC << endl;
	s1->setLength(3);
	for (int i=0; i<nR; i++) {
		cout << "\nChecking row " << i;
		for (int j=0; j<nC; j++) {
			cout << "\nChecking column" << j << endl;
			cout << "HW X: " << s1->checkHorz(i, 'X') << " ";
			cout << "HW O: " << s1->checkHorz(i, 'O') << " ";
			cout << "VW X: " << s1->checkVert(i, j, 'X') << " ";
			cout << "VW O: " << s1->checkVert(i, j, 'O') << " ";
			cout << "DW X: " << s1->checkDiag(i, j, 'X') << " ";
			cout << "DW O: " << s1->checkDiag(i, j, 'O') << " ";
		}
	}

}