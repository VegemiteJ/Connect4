#include "Player.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Player::Player(int Cols, int Rows)
{
	numRows = Rows;
	numColumns = Cols;
}

int Player::play() {
	int choice = 0;

	cout << "Enter a column in which to place your token (1 ... " << numColumns << "): " << endl;
	cin >> choice;
	if (choice == -1) {
		exit(1);
	}

	return choice;
}