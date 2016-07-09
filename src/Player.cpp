#include "Player.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Player::Player(int Cols, int Rows, Board* iBoard)
{
	numRows = Rows;
	numColumns = Cols;
	board = iBoard;
}