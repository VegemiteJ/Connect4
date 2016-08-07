#include <iostream>
#include "connectfour.h"

using namespace std;

connectfour::connectfour()
{
	for (int i=0; i<6; i++)
	{
		for (int j=0; j<7; j++)
		{
			board[i][j] = 0;
		}
	}
}

void connectfour::clearlastmove(int i)
{
	for (int w=0; w<6; w++)
	{
		if (board[w][i]!=0)
		{
			board[w][i]=0;
			w=6;
		}

	}
}

bool connectfour::iswinningmove(int i, int oneortwo)
{
	//Checks for possible winning move for self
	if (!makemove(i+1,oneortwo))
	{
		return false;
	}
	if (gamewon())
	{
		clearlastmove(i);
		return true;
	}
	//If it doesn't win it reverts the move
	else
	{
		clearlastmove(i);
		return false;
	}
}


int connectfour::ai_move(int player)
{
	//First move
	bool boardempty = true;
	for (int i=0; i<6; i++)
	{
		for (int j=0; j<7; j++)
		{
			if (board[i][j] != 0)
			{
				j,i=7;
				boardempty = false;
			}
		}
	}
	if (boardempty)
	{
		makemove(4,player);
		return 0;
	}

	//If winning move for self is available makes it
	for (int i=0; i<7; i++)
	{
		if (iswinningmove(i,player))
		{
			makemove(i+1,player);
			return 0;
		}
	}
	//Gets other players number
	int otherplayer;
	if (player == 1) { otherplayer = 2; }
	if (player == 2) { otherplayer = 1; }
	bool check;

	//Checks for possible winning move for opponent and blocks it
	for (int i=0; i<7; i++)
	{
		if (iswinningmove(i,otherplayer))
		{
			makemove(i+1,player);
			return 0;
		}
	}

	//Checks if we can make a move that allows a winning move next turn
	for (int i=0; i<7; i++)
	{
		check = makemove(i+1,player);
		for (int j=0; j<7; j++)
		{
			if (iswinningmove(j,player))
			{
				//Checks we don't create a winning move for the other player
				bool winningmove = false;
				for (int w=0; w<7; w++)
				{
					if (iswinningmove(w,otherplayer))
					{
						cout <<"CHECK1" << endl;
						winningmove = true;
						clearlastmove(i);
						w=7;
					}
				}
				if (!winningmove)
				{
					cout <<"CHECK4" << endl;

					return 0;
				}
			}
		}
		if (check) 
		{ 
			clearlastmove(i); 
		}
	}

	//Checks if we can make a move that allows for a win 2 moves in advance
	for (int i=0; i<7; i++)
	{
		check = makemove(i+1,player);
		for (int j=0; j<7; j++)
		{
			bool check1 = makemove(j+1,player);
			for (int w=0; w<7; w++)
			{
				if (iswinningmove(w,player))
				{
					clearlastmove(j);
					bool winningmove = false;
					cout <<"CHECK2" << endl;
					for (int x=0; x<7; x++)
					{
						if (iswinningmove(x,otherplayer))
						{
							winningmove = true;
							x=7;
						}
					}
					if (!winningmove)
					{
						return 0;
					}
					else
					{
						makemove(j+1,player);
					}
				}
			}
			if (check1) { clearlastmove(j); }
		}
		if (check) { clearlastmove(i); }
	}
	
	for (int i=0; i<7; i++)
	{
		check = makemove(i+1,player);
		bool winningmove = false;
		for (int j=0; j<7; j++)
		{
			if (iswinningmove(j,otherplayer))
			{
				winningmove = true;
				j=7;
			}
			if (!winningmove)
			{
				return 0;
			}
			else if(check)
			{
				clearlastmove(i);
			}
		}
	}
}

bool connectfour::gamewon()
{
	bool gamewon = false;
	for (int i=0; i<6; i++)
	{
		for (int j=0; j<6; j++)
		{
			if (board[i][j] != 0)
			{
				int piece = board[i][j];
				int count = 1;
				//Check horizontal '-'
				if (j<4)
				{
					for (int w=1; w<4; w++)
					{
						if (board[i][j+w]==piece)
						{
							count++;
						}
						if (count==4)
						{
							return true;
						}
					}
				}
				count = 1;
				//check vertical '|'
				if (i<3)
				{
					for (int w=1; w<4; w++)
					{
						if (board[i+w][j]==piece)
						{
							count++;
						}
						if (count==4)
						{
							return true;
						}
					}
				}
				count = 1;
				//check diagonal '\'
				if (j<4 && i<3)
				{
					for (int w=1; w<4; w++)
					{
						if (board[i+w][j+w]==piece)
						{
							count++;
						}
					}
					if (count==4)
					{
						return true;
					}
				}
				count = 1;
				//check diagonal '/'
				if (j>2 && i<3)
				{
					for (int w=1; w<4; w++)
					{
						if (board[i+w][j-w]==piece)
						{
							count++;
						}
					}
					if (count==4)
					{
						return true;
					}
				}
			}
		}
	}
	return gamewon;
}

bool connectfour::makemove(int collumn, int one)
{
	bool successfulmove = false;
	if (collumn > 7 || collumn < 0)
	{
		return false;
	}
	for (int i=5; i>=0; i--)
	{
		if (board[i][collumn-1] == 0)
		{
			board[i][collumn-1] = one;
			successfulmove = true;
			i=-1;
		}
	}
	return successfulmove;
}

void connectfour::printboard()
{
	cout << "-----------------------------" << endl;
	for (int i=0; i<6; i++)
	{
		cout << "|";
		for (int j=0; j<7; j++)
		{
			if (board[i][j] == 0)
			{
				cout << "   ";
			}
			if (board[i][j] == 1)
			{
				cout << " X ";
			}
			if (board[i][j] == 2)
			{
				cout << " O ";
			}
			cout << "|";
		}
		cout << endl << "-----------------------------" << endl;
	}
	cout << "  1   2   3   4   5   6   7" << endl;
}

bool connectfour::boardfull()
{
	bool boardfull = true;
	for (int i=0; i<6; i++)
	{
		for (int j=0; j<7; j++)
		{
			if (board[i][j] == 0)
			{
				boardfull = false;
			}
		}
	}
	return boardfull;
}

void connectfour::twoplayergame()
{
	int player = 2;
	while(!gamewon())
	{
		if (player == 1)
		{
			player = 2;
		}
		else
		{
			player = 1;
		}
		int move;
		cin >> move;
		//Handling Illegal input
		while (!(move == 1 || (move == 2) || (move == 3) || (move == 4) || move == 5 || move == 6 || move == 7))
		{
			printboard();
			cout << "Illegal move" << endl;
			cin >> move;
		}
		//Makes sure the collumn isn't full
		bool successfulmove = (makemove(move,player));
		while (!successfulmove)
		{
			printboard();
			cout << "Illegal move" << endl;
			cin >> move;
			successfulmove = makemove(move,player);
		}
		printboard();
		if (boardfull()) { break; }
	}
	if (boardfull())
	{
		cout << "The game is a draw!" << endl;
	}
	else
	{
		cout << "player " << player << " has won!" << endl;
	}
}

void connectfour::ai_game()
{
	int turn = 2;
	bool turncounter = true;
	while(!gamewon())
	{
		if (turncounter)
		{
			ai_move(1);
			printboard();
		}
		else
		{
			int move;
			cin >> move;
			while (!(move == 1 || (move == 2) || (move == 3) || (move == 4) || move == 5 || move == 6 || move == 7))
			{
				
				printboard();
				cout << "Illegal move" << endl;
				cin >> move;
			}
			bool successfulmove = (makemove(move,turn));
			while (!successfulmove)
			{
				printboard();
				cout << "Illegal move" << endl;
				cin >> move;
				successfulmove = makemove(move,turn);
			}
			printboard();
		}
		turncounter = !turncounter;
	}
}