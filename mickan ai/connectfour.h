#include <iostream>

class connectfour
{
public:
	connectfour(); //Constructor creates the board set to 0
	bool gamewon(); //Checks if the game is won
	void printboard(); //Prints the current board
	bool makemove(int collumn, int num); //Places a piece in the input collumn
	void twoplayergame(); //Plays the game
	bool boardfull(); //Checks if the board is full
	int ai_move(int numb); //Computes the AI's move
	bool iswinningmove(int collumn, int number); //Checks if the input move is a winning one
	void clearlastmove(int collumn); //Deletes move in set collumn
	void ai_game(); //Runs a game against the AI
private:
	int board[6][7];
};