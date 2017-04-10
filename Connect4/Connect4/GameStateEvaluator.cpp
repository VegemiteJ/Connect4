#include "GameStateEvaluator.h"
#include <iostream>
using namespace std;

#pragma region WinStatusImplementation

bool GameStateEvaluator::CheckVertical(Matrix* state, int row, int col, Move p, int ConnectLength, int NumRow, int NumCol)
{
    Matrix stateDeRef = *state;
    // Only check if there are at least n in the current column
    if (row <= NumRow - ConnectLength)
    {
        bool sameToken = true;
        // Check the cells below for consecutiveness
        for (int i = row; i<row + ConnectLength; i++)
        {
            if (stateDeRef(i,col) != p)
            {
                sameToken = false;
                break;
            }
        }
        if (sameToken == true)
        {
            return true;
        }
    }
    return false;
}

bool GameStateEvaluator::CheckHorizontal(Matrix* state, int row, int col, Move p, int ConnectLength, int NumRow, int NumCol)
{
    Matrix stateDeRef = *state;
    // Search any that still have n more
    for (int i = 0; i<NumCol - (ConnectLength - 1); i++)
    {
        bool status = true;
        for (int j = 0; j<ConnectLength; j++) {
            status = status && (stateDeRef(row,i + j) == p);
            if (!status)	//Slight speedup by not performing rest of the checks
                break;
        }
        //If all still true, must have that many in a row
        if (status)
            return true;
    }
    return false;
}

bool GameStateEvaluator::CheckDiagonal(Matrix* state, int _row, int _col, Move p, int ConnectLength, int NumRow, int NumCol)
{
    if (!CheckPosition(state, _row, _col, p, NumRow, NumCol))
        return false;
    bool hasWon = false;

    //Check leftUp/DownRight diagonals
    //----------------------------------------------
    int leftRun = 1;
    //cout << "Checking LeftUP" << endl;
    int leftUpperCount = 1;
    bool stillValid = true;
    while (stillValid) {
        //Calculate new index
        int row = _row - leftUpperCount;
        int col = _col - leftUpperCount;
        //cout << "Row: " << row << "Col: " << col << endl;

        //Check if in bounds and run token Test
        stillValid = CheckPosition(state, row, col, p, NumRow, NumCol);
        if (stillValid) {
            leftUpperCount++;
            leftRun++;
        }
    }

    //cout << "Checking RightDown" << endl;
    int rightLowerCount = 1;
    stillValid = true;
    while (stillValid) {
        //Calculate new index
        int row = _row + rightLowerCount;
        int col = _col + rightLowerCount;
        //cout << "Row: " << row << "Col: " << col << endl;

        //Check if in bounds and run token Test
        stillValid = CheckPosition(state, row, col, p, NumRow, NumCol);
        if (stillValid) {
            rightLowerCount++;
            leftRun++;
        }
    }
    //cout << "Left upper results: " << rightLowerCount << ", " << leftRun << endl;
    if (leftRun >= ConnectLength) {
        hasWon = true;
        return true;
    }

    //Check rightUP/DownLeft diagonal
    //---------------------------------------------
    int rightRun = 1;

    //cout << "Checking RightUP" << endl;
    int rightUpperCount = 1;
    stillValid = true;
    while (stillValid) {
        //Calculate new index
        int row = _row - rightUpperCount;
        int col = _col + rightUpperCount;
        //cout << "Row: " << row << "Col: " << col << endl;

        //Check if in bounds and run token Test
        stillValid = CheckPosition(state, row, col, p, NumRow, NumCol);
        if (stillValid) {
            rightUpperCount++;
            rightRun++;
        }
    }
    //cout << "Right upper results: " << rightUpperCount << ", " << rightRun << endl;

    //cout << "Checking LeftDown" << endl;
    int leftLowerCount = 1;
    stillValid = true;
    while (stillValid) {
        //Calculate new index
        int row = _row + leftLowerCount;
        int col = _col - leftLowerCount;
        //cout << "Row: " << row << "Col: " << col << endl;

        //Check if in bounds and run token Test
        stillValid = CheckPosition(state, row, col, p, NumRow, NumCol);
        if (stillValid) {
            leftLowerCount++;
            rightRun++;
        }
    }
    //cout << "Left Lower results: " << leftLowerCount << ", " << rightRun << endl;
    if (rightRun >= ConnectLength) {
        hasWon = true;
        return true;
    }
    return hasWon;
}

//Marked as inline due to frequent calls
inline bool GameStateEvaluator::CheckPosition(Matrix* state, int row, int col, Move p, int NumRow, int NumCol)
{
    Matrix stateDeRef = *state;
    
    //Check if in bounds
    if (row >= NumRow || col >= NumCol || row < 0 || col < 0) {
        return false;
    }

    //Perform the token test
    if (stateDeRef(row,col) == p) {
        return true;
    }
    else {
        return false;
    }
}

bool GameStateEvaluator::CheckWin(Board * state, Move p)
{
    int NumRow = state->NumRow;
    int NumCol = state->NumCol;
    int MoveRow = state->MoveRow;
    int MoveCol = state->MoveCol;
    int ConnectLength = state->ConnectLength;
    Matrix* rawState = state->StateAccess();

    //When no move, noone could have won
    if (MoveCol == -1 || MoveRow == -1)
        return false;

    if (CheckVertical(rawState, MoveRow, MoveCol, p, ConnectLength, NumRow, NumCol))
        return true;
    if (CheckHorizontal(rawState, MoveRow, MoveCol, p, ConnectLength, NumRow, NumCol))
        return true;
    if (CheckDiagonal(rawState, MoveRow, MoveCol, p, ConnectLength, NumRow, NumCol))
        return true;

    return false;
}

///General algorithm is to find all empty spaces
///	For every direction in the 8 move directions
///		Follow that branch until connectLength tokens are seen
///			Add this as the count for that position, continue for all other positions
int GameStateEvaluator::CountN(Matrix* state, Move p, int connectLength)
{
	return 0;
}

///Given a location on the board, follow that desired token until it is as long as connectLength
int GameStateEvaluator::CountNFromLocation(Matrix * rawState, int row, int col, Move p, int connectLength)
{
	int numberMatchesFound = 0;
	
	//Firstly search all 8 neighbours for the desired token
	// Neighbour defined by [][][]
	//						[][A][]
	//						[][][]
	//	Check within bounds of the board
	
	//Defines the enums to add to the current position, defining the next areas to check
	int rowChkEnums[8] = {-1,-1,-1,0,0,1,1,1};
	int colChkEnums[8] = {-1,0,1,-1,1,-1,0,1};

	for (int i = 0; i < 8; i++)
	{
		int currRow = row + rowChkEnums[i];
		int currCol = col + colChkEnums[i];
		cout << "Evaluating Postion: " << currRow << "," << currCol << endl;
		cout << "\tBounds? " << rawState->checkBounds(currRow, currCol) << endl;
		//If either our of range of the board
		if (!rawState->checkBounds(currRow, currCol)) {
			continue;
		}

		//Now continue along that path, counting tokens
		//	While count along this direction is less than or equal to connectLength
		//		Also while within bounds
		//		Also while token at that location == one we are checking
		//	Direction is currRow+rowChkEnums[i], currCol+colChkEnums[i]
		int count = 0;
		while (rawState->checkBounds(currRow, currCol) &&
			(*rawState)(currRow, currCol) == p &&
			count < connectLength)
		{
			count++;
		}

		cout << "\tDone" << endl;
		
	}

	return numberMatchesFound;
}

///Utility is zero sum
///	Returns the count of player p 3 in a row - player 2 3 in a row
int GameStateEvaluator::ComputeThreeInRow(Board * state, Move p)
{
	int NumRow = state->NumRow;
	int NumCol = state->NumCol;
	int MoveRow = state->MoveRow;
	int MoveCol = state->MoveCol;
	int ConnectLength = state->ConnectLength;
	Matrix* rawState = state->StateAccess();

	if (MoveCol == -1 || MoveRow == -1)
		return 0;

	int count3sP1 = CountN(rawState, p, 3);
	int count3sP2 = CountN(rawState, ((p==1)?P2_MOVE:P1_MOVE), 3);

	return count3sP1 - count3sP2;
}

#pragma endregion

///Idea is to compute all the various heuristics and to return the best linear combination
///	TODO in future: apply the reinforcement learning component to learn the best combination of the heuristics
int GameStateEvaluator::ComputeUtility(Board * evaluationPosition, Move p)
{
	int threeStatUtil = ComputeThreeInRow(evaluationPosition, p);

	return threeStatUtil;
}

int GameStateEvaluator::ComputeWinUtility(Board * evaluationPosition, Move p, Move player)
{
    //Utility to return is +1000 if we won, -1000 if opponent won
    return (p == player ? 1000 : -1000);
}
