#include "LocalPlayer.h"
#include <iostream>
#include <cstdlib>

using namespace std;

//Initialise new local player
LocalPlayer::LocalPlayer(int numRows, int numCols, Board* iboard)
	: Player(numRows, numCols, iboard) 
{
	id = 0;
}

LocalPlayer::LocalPlayer(Board* m_board) 
	: Player(m_board)
{
	id = 0;
}


LocalPlayer::~LocalPlayer() {}

//Inherited Classes from Player
void LocalPlayer::initialise() {}
void LocalPlayer::setFirst() {}
void LocalPlayer::Exit(bool val) {}

//Prompt the human player for a move via CLI
int LocalPlayer::play(bool valid) 
{
	int choice = 0;
	if (!valid)
		cout << "Last move was INVALID....." << endl;

	cout << "Enter a column in which to place your token (1 ... " << numColumns << "): " << endl;
	cin >> choice;
	if (choice == -1) {
		exit(1);
	}

	return choice;
}