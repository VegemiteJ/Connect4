#include "Node.h"
#include "consts.h"
#include "ColourDef.h"
#include <iostream>

int global_id = 0;

using namespace std;

//Public Constructors
//---------------------------------------------------
Node::Node() {}	//Unused

Node::Node(int iID, GameState* iinitial, int initial_turn) :
	ID(iID), thisMoveColumn(-1), numChildren(-1), thisTurn(initial_turn), 
	allocated(0), myUtil(0), childUtil(NULL), myChildren(NULL), 
	parent(NULL), state(iinitial) {}

Node::Node(int iID, GameState* parent_state, int new_mov_column, int new_turn) :
	ID(iID), thisMoveColumn(new_mov_column), numChildren(-1), thisTurn(new_turn), 
	allocated(0), myUtil(0), childUtil(NULL), myChildren(NULL), 
	parent(NULL), state(parent_state) {}

//Public Destructors
//---------------------------------------------------
Node::~Node() 
{
	if (verbose>3)
		cout << "Deleting node: " << ID << endl;
	if (allocated==1)
		delete[] childUtil;
}
void Node::DeleteTree() 
{

}

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
	if (verbose>3) {
		cout << "Discover Children..." << endl;
		cout << "Num Rows: " << state->numRows << "Num Cols: " << state->numCols << endl;
	}
	numChildren = 0;

	int terminalPosition = 0;
	int* children = new int[state->numCols];

	//Discover number of children
	for (int i=0; i<state->numCols; i++) {
		if (state->checkValidMove(i)){
			children[numChildren++] = i;
			terminalPosition++;
			if (verbose >3)
				cout << "Column: " << i << " " << children[numChildren-1];
		}
	}
	if (verbose >3)
		cout << "NumChild: " << numChildren << endl;
	if (numChildren != 0) {
		myChildren = new Node*[numChildren];
		childUtil = new int[numChildren]();
		allocated = 1;
	}
	for (int i = 0; i<terminalPosition; i++){
		if (verbose>3)
			cout << "Making node: " << i << endl;
		myChildren[i] = new Node(global_id++, state, children[i], (thisTurn+1)%2);
	}
	//Free local scope children array
	delete[] children;

	return myChildren;
}

int Node::ComputeUtil() 
{
	int winStat = WinUtil();
	if (winStat != 0) {
		myUtil = winStat;
		return winStat;
	}
	int h1Stat = H1Util();
	if (h1Stat != 0) {
		myUtil = h1Stat;
		return h1Stat;
	}
	//Purely neutral statistic
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
	if (verbose>3)
		cout << "Unmoving... Row: " << thisMoveRow+1 << " Col: " << thisMoveColumn+1 << endl;
	state->cell_array[thisMoveRow][thisMoveColumn] = ' ';
}
int Node::WinUtil() 
{
	char thisTurnToken = (thisTurn==0) ? 'X' : 'O';
	char currentCheckToken1 = 'X';
	char currentCheckToken2 = 'O';
	if (verbose>3) {
		cout << "thisTurnToken = " << thisTurnToken << endl;
		cout << "Stat1: " << state->checkWin(currentCheckToken1) << " " << (currentCheckToken1==thisTurnToken) << endl;
		cout << "Stat2: " << state->checkWin(currentCheckToken2) << " " << (currentCheckToken2==thisTurnToken) << endl;
	}
	// If this turn has won, return max util
	if (state->checkWin(currentCheckToken1) && currentCheckToken1 == thisTurnToken)
	{
		if (verbose >3)
			cout << "Player X Appears to have won, returning max utility" << endl;
		int base = 1000;
		return base;
	}
	else if (state->checkWin(currentCheckToken2) && currentCheckToken2 == thisTurnToken)
	{
		if (verbose >3)
			cout << "Player O Appears to have won, returning min utility" << endl;
		int base = -1000;
		return base;
	}
	return 0;
}
int Node::H1Util() 
{
	return 0;
}
int Node::ConnectivityUtil() 
{
	return 0;
}