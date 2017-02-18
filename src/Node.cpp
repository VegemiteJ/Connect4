#include "stdafx.h"
#include "Node.h"
#include "Consts.h"
#include "ColourDef.h"
#include "PrintConsole.h"
#include <iostream>
#include <chrono>
#include <thread>

int global_id = 0;

using namespace std;

//Public Constructors
//---------------------------------------------------
Node::Node() {}	//Unused

Node::Node(int iID, GameState* iinitial, int initial_turn) :
	ID(iID), thisMoveColumn(-1), thisMoveRow(-1), numChildren(-1),
	thisTurn(initial_turn), allocated(0), myUtil(0), numRandSwaps(3),
	heuristics(12),myChildren(NULL), parent(NULL), state(iinitial)
	{
		PrintConsole("Constructor 0 called...\n", 3);
		childUtil = new int[state->numCols];
		allocated = 1;
		generator.seed((unsigned int)chrono::system_clock::now().time_since_epoch().count());
		distribution = uniform_int_distribution<int>(1,state->numCols);
		dice = bind(distribution, generator);
	}

Node::Node(int iID, GameState* parent_state, int new_mov_column, int new_turn) :
	ID(iID), thisMoveColumn(new_mov_column), thisMoveRow(-1), numChildren(-1),
	thisTurn(new_turn), allocated(0), myUtil(0), numRandSwaps(3),
	heuristics(12), myChildren(NULL), parent(NULL), state(parent_state) 
	{
		PrintConsole("Constructor 1 called...\n", 3);
		childUtil = new int[state->numCols];
		allocated = 1;
		generator.seed((unsigned int)chrono::system_clock::now().time_since_epoch().count());
		distribution = uniform_int_distribution<int>(1,state->numCols);
		dice = bind(distribution, generator);
	}

//Constructors for heuristic calls
Node::Node(int iID, GameState* iinitial, int initial_turn, int heuristic, int randSwaps) :
	ID(iID), thisMoveColumn(-1), thisMoveRow(-1), numChildren(-1),
	thisTurn(initial_turn), allocated(0), myUtil(0), numRandSwaps(randSwaps),
	heuristics(heuristic), myChildren(NULL), parent(NULL), state(iinitial)
	{
		PrintConsole("Constructor 2 called...\n", 3);
		PrintConsole("Heuristic set to: " + to_string(heuristic) + "\n", 3);

		childUtil = new int[state->numCols];
		allocated = 1;
		generator.seed((unsigned int)chrono::system_clock::now().time_since_epoch().count());
		distribution = uniform_int_distribution<int>(1,state->numCols);
		dice = bind(distribution, generator);
	}

Node::Node(int iID, GameState* parent_state, int new_mov_column, int new_turn,
	int heuristic, int randSwaps) :
	ID(iID), thisMoveColumn(new_mov_column), thisMoveRow(-1), numChildren(-1),
	thisTurn(new_turn), allocated(0), myUtil(0), numRandSwaps(randSwaps),
	heuristics(heuristic), myChildren(NULL), parent(NULL), state(parent_state) 
	{
		PrintConsole("Constructor 3 called...\n", 3);
		PrintConsole("Heuristic set to: " + to_string(heuristic) + "\n", 3);
		childUtil = new int[state->numCols];
		allocated = 1;
		generator.seed((unsigned int)chrono::system_clock::now().time_since_epoch().count());
		distribution = uniform_int_distribution<int>(1,state->numCols);
		dice = bind(distribution, generator);
	}


//Public Destructors
//---------------------------------------------------
Node::~Node() 
{
	PrintConsole("Deleting node: " + to_string(ID) + "\n", 3);
	if (allocated==1) {
		delete[] childUtil;		//Why does New[] throwing segfault after 15 deep or so on linux
								//Mem usage is only 800MB for 15 deep... so that isn't the issue
	} else if (allocated>1) {
		delete[] myChildren;
		delete[] childUtil;
	}

}

Node::Node( Node &obj ) {}

void Node::DeleteTree() {}

//Public Member Functions
//---------------------------------------------------
GameState* Node::GetState()
{
	//Return a copy of the game state
	return state;
}
int Node::GetTurn() 
{
	return thisTurn;
}
int Node::GetDepth() 
{
	return 0;
}
int Node::GetNumberOfChildren() 
{
	return numChildren;
}
int Node::GetUtil() 
{
	return myUtil;
}
int* Node::GetChildrenUtil() 
{
	return childUtil;
}
Node** Node::GetChildren() 
{
	return myChildren;
}
int Node::GetMove() 
{
	return thisMoveColumn;
}

Node** Node::DiscoverChildren() 
{
	PrintConsole("Discover Children...\n", 3);
	PrintConsole("Num Rows: " + to_string(state->numRows), 3);
	PrintConsole("Num Cols: " + to_string(state->numCols) + "\n", 3);

	numChildren = 0;

	int terminalPosition = 0;
	//Provide static lookup for number of
	int children[7];

	//Discover number of children
	for (int i=0; i<state->numCols; i++) {
		if (state->checkValidMove(i)){
			children[numChildren++] = i;
			terminalPosition++;
			PrintConsole("Column: " + to_string(i) + to_string(children[numChildren-1]), 3);
			PrintConsole("\n",3);
		}
	}
	
	PrintConsole("NumChild: " + to_string(numChildren), 3);

	if (numChildren != 0) {
		myChildren = new Node*[numChildren];
		childUtil = new int[numChildren]();		//Why is New[] throwing segfault????
		allocated = 2;

		PrintConsole("Before Swap addresses are:\n", 3);
		for (int i = 0; i<state->numCols; i++) {
			PrintConsole(to_string(children[i]) + ",",3);
		} PrintConsole("\n",3);

		for (int i=0; i<numRandSwaps; i++) {
			//Swap two random elements
			int a = dice()%numChildren;
			int b = dice()%numChildren;
			Swap(children + a, children + b);
		}

		PrintConsole("After Swap addresses are:\n", 3);
		for (int i = 0; i<state->numCols; i++) {
			PrintConsole(to_string(children[i]) + ",",3);
		} PrintConsole("\n",3);

		for (int i = 0; i<terminalPosition; i++){
			PrintConsole("Making node " + to_string(i) + "\n", 3);
			myChildren[i] = new Node(global_id++, state, children[i],
									(thisTurn+1)%2, heuristics, numRandSwaps);
		}
	}
	//Free local scope children array
	//delete[] children;	Why is New[] throwing segfault????

	return myChildren;
}

int Node::ComputeUtil() 
{
	if ( ((heuristics >> 3) & 1) == 1) {
		int winStat = WinUtil();
		if (winStat != 0) {
			myUtil = winStat;
			return winStat;
		}	
	}
	if ( ((heuristics >> 2) & 1) == 1) {
		int h1Stat = H1Util();
		if (h1Stat != 0) {
			myUtil = h1Stat;
			return h1Stat;
		}
	}
	if ( ((heuristics >> 1) & 1) == 1) {
		//Do nothing as c2 not implemented
	}
	if ( ((heuristics >> 0) & 1) == 1) {
		//Do nothing as cprime not implemented
	}

	//Purely neutral statistic for all zero
	myUtil = 0;
	return 0;
}
void Node::Print() 
{
	cout << "\nID: " << ANSI_PURPLE << ID << ANSI_RESET;
	cout << " Number of Children: " << ANSI_PURPLE;
	cout << numChildren << ANSI_RESET;
	cout << " Turn: " << ANSI_PURPLE << thisTurn << ANSI_RESET;
	cout << endl;
	state->print();
	cout << "Last Move: " << state->LastMoveRow + 1 << " " << state->LastMoveCol + 1 << endl;
	cout << "X Win?: " << state->checkWin('X') << ", O Win?: " << state->checkWin('O') << endl;
	cout << "This State Utility: " << ANSI_PURPLE << ComputeUtil() << ANSI_RESET << "\n" << endl;
	if ( ((heuristics >> 3) & 1) == 1)
		PrintConsole("Heuristic bit 3 set\n", 3);

	if ( ((heuristics >> 2) & 1) == 1)
		PrintConsole("Heuristic bit 2 set\n", 3);

	if ( ((heuristics >> 1) & 1) == 1)
		PrintConsole("Heuristic bit 1 set\n", 3);

	if ( ((heuristics >> 0) & 1) == 1)
		PrintConsole("Heuristic bit 0 set\n", 3);

}

//Private Member Functions
//---------------------------------------------------
void Node::Move() 
{
	char turn = (thisTurn == 0) ? 'X' : 'O';
	state->update_cell(thisMoveColumn, turn);
	thisMoveRow = state->LastMoveRow;
}
void Node::UnMove() 
{
	PrintConsole("Unmoving... Row: " + to_string(thisMoveRow+1) + " ",3);
	PrintConsole(" Col: " + to_string(thisMoveColumn+1) + "\n",3);
	char** st = state->getState();
	st[thisMoveRow][thisMoveColumn] = ' ';
}
int Node::WinUtil() 
{
	char thisTurnToken = (thisTurn==0) ? 'X' : 'O';
	char currentCheckToken1 = 'X';
	char currentCheckToken2 = 'O';
	PrintConsole("thisTurnToken = " + to_string(thisTurnToken) + "\n",3);
	PrintConsole("Stat1: " + to_string(state->checkWin(currentCheckToken1)) + " ",3);
	PrintConsole(to_string(currentCheckToken1==thisTurnToken) + "\n",3);
	PrintConsole("Stat2: " + to_string(state->checkWin(currentCheckToken2)) + " ",3);
	PrintConsole(to_string(currentCheckToken2==thisTurnToken) + "\n",3);
	// If this turn has won, return max util
	if (state->checkWin(currentCheckToken1) && currentCheckToken1 == thisTurnToken)
	{
		PrintConsole("Player X Appears to have won, returning max utility\n",3);
		int base = 1000;
		return base;
	}
	else if (state->checkWin(currentCheckToken2) && currentCheckToken2 == thisTurnToken)
	{
		PrintConsole("Player O Appears to have won, returning min utility\n",3);
		int base = -1000;
		return base;
	}
	return 0;
}

int Node::H1Util() 
{
	//Number of X and O in a row
	int count[2] = {0,0};
	
	char currentToken = 'X';
	count[0] = Count3(currentToken);

	currentToken = 'O';
	count[1] = Count3(currentToken);

	PrintConsole("Number of 3 in a row for X: " + to_string(count[0]) + "\n",3);
	PrintConsole("Number of 3 in a row for O: " + to_string(count[1]) + "\n",3);

	return 50*(count[0]-count[1]);
}

int Node::DetermineDirection(int k, int l)
{
	int val = l+k;
	val = (val<0) ? -val : val;

	if (val==2)			//Left diag
		return 0;
	else if (val==0)	//Right diag
		return 1;
	else if (l==0)		//Vertical
		return 2;
	else if (k==0)		//Horizontal
		return 3;

	//Error
	return -1;
}

int Node::Count3(char Token)
{
	int nRows = state->numRows;
	int nCols = state->numCols;

	int count = 0;

	char** brd = state->getState();

	//For each square on board not already seen
	for (int i=0; i<nRows; i++) {
		for (int j=0; j<nCols; j++) {
			if ( (brd[i][j] == ' ')) {		//If current square is blank
				//Initialise array of 4 ints storing the number in a row in each dimension
				int countInDimension[4] = {0,0,0,0};	//1 for including self

				//Check from this position - all neighbouring pieces
				for (int k=-1; k<=1; k++) {		//While in bounds rows, columns
					if ((i+k < nRows && i+k >= 0)) {
						for (int l=-1; l<=1; l++) {
							if ((j+l >= 0) && (j+l < nCols) && (k!=0 || l!=0)) {
								//If current neighbour is unvisited, continue down that dimension incrementing length
								//Only continue if unvisited && token is same one && not out of bounds
								int row = i+k;
								int col = j+l;
								int index = DetermineDirection(k,l);
								while (brd[row][col] == Token) {
									//cout << "Position: (" << row << "," << col << ") is " << Token << endl;
									countInDimension[index]++;

									row += k; col += l;
									if (row<0 || row>=nRows || col<0 || col>=nCols) {	//Out of bounds
										break;
									}
								}
							}
						}
					}
				}
				//cout << "Dimension details: " << countInDimension[0] << " " << countInDimension[1] << " " << countInDimension[2] << " " << countInDimension[3] << endl;
				int max = 0;
				for (int m=0; m<4; m++) {
					if (countInDimension[m] > max) {
						max = countInDimension[m];
					}
				}
				if (max == 3) {
					//cout << "Found a 3 in Row for " << Token << " at: (" << i << "," << j << ")" << endl;
					count++;
				}
			}
		}
	}

	return count;
}

int Node::ConnectivityUtil() 
{
	return 0;
}

void Node::Swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
