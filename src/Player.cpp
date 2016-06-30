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

	do
	{
		cout << "Enter a column in which to place your token (1 ... " << numColumns << "): " << endl;
		cin >> choice;
		if (choice == -1) {
			exit(1);
		}
	} while (choice < 1 || choice > numColumns);
	// Adjust so it fits with array indexing (0-COLUMNS-1)
	choice--;

	return --choice;
}