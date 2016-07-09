#include "LocalPlayer.h"
#include <iostream>
#include <cstdlib>

using namespace std;

LocalPlayer::LocalPlayer(int numRows, int numCols, Board* iboard)
	: Player(numRows, numCols, iboard) {}

LocalPlayer::~LocalPlayer() {}

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