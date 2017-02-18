#include "stdafx.h"
#include "Player.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Player::Player(int inumRows, int inumCols, Board* iBoard) : 
	turn (-1), id (-1), numRows(inumRows), 
	numColumns(inumCols), board(iBoard)	{}

Player::Player(Board* m_board) :
	turn(-1), id(-1), numRows(m_board->GetRow()), 
	numColumns(m_board->GetCol()), board(m_board) {}

Player::~Player() 
{
	delete board;
}