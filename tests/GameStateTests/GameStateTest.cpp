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
	int* size = board->getSize();

	GameState* board1 = new GameState(board->getBoardState(), size[0], size[1]);
	
	cout << "Original... reset:" << endl;
	board->resetBoard();
	board->print();
	delete board;

	cout << "GameState:" << endl;
	board1->print();

	cout << "GameState move: (3rd column, player X)" << endl;
	GameState* board2 = new GameState(board1, 2, 0);
	cout << "Dimensions: " << board2->numRows << " " << board2->numCols << endl;
	board2->print();
	cout << "Row Specific" << endl;
	GameState* board3 = new GameState(board1, 1, 2, 0);
	cout << "Dimensions: " << board3->numRows << " " << board3->numCols << endl;
	board3->print();

	cout << "Empty initialiser-different Sizes" << endl;
	GameState** arrOfStates = new GameState*[8];
	for (int i = 1; i <= 8; ++i)
	{
		cout << "State: " << i << endl;
		arrOfStates[i] = new GameState(i,i);
		cout << "Dimensions: " << arrOfStates[i]->numRows << " " << arrOfStates[i]->numCols << endl;
		arrOfStates[i]->print();
	}

	default_random_engine generator = minstd_rand0(12345);
	uniform_int_distribution<int> distribution = uniform_int_distribution<int>(2,6);
	function<int()> dice = bind(distribution, generator);

	cout << "Empty initialiser-Randomly Populated, different Sizes" << endl;
	GameState** arrOfStates1 = new GameState*[4];
	for (int i = 0; i < 4; i++)
	{
		int nR = dice();
		int nC = dice();
		cout << "Dimensions: " << nR << " " << nC << endl;
		arrOfStates1[i] = new GameState(nR,nC);

		//Lol this bit
		for (int j=0; j < dice() %(nR*nC); j++)
		{
			arrOfStates1[i]->cell_array[dice() % nR][dice() % nC] = (dice()%2 == 0) ? 'X' : 'O';
		}

		arrOfStates1[i]->print();
	}

}