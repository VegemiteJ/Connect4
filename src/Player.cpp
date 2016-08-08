#include "Player.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Player::Player(int inumRows, int inumCols, Board* iBoard)
{
	numRows = inumRows;
	numColumns = inumCols;
	board = iBoard;
}

Player::~Player() 
{
	delete board;
}