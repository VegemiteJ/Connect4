#include "Player.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Player::Player(int numRows, int numCols, Board* iBoard)
{
	numRows = Rows;
	numColumns = Cols;
	board = iBoard;
}

Player::~Player() 
{
	delete board;
}