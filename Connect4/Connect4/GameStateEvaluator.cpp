#include "GameStateEvaluator.h"

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

    if (CheckVertical(rawState, MoveRow, MoveCol, p, ConnectLength, NumRow, NumCol))
        return true;
    if (CheckHorizontal(rawState, MoveRow, MoveCol, p, ConnectLength, NumRow, NumCol))
        return true;
    if (CheckDiagonal(rawState, MoveRow, MoveCol, p, ConnectLength, NumRow, NumCol))
        return true;

    return false;
}

#pragma endregion

int GameStateEvaluator::ComputeUtility(Board * evaluationPosition, int _depth)
{
    return 0;
}

int GameStateEvaluator::ComputeWinUtility(Board * evaluationPosition, Move p, Move player)
{
    //Utility to return is +1000 if we won, -1000 if opponent won
    return (p == player ? 1000 : -1000);
}
