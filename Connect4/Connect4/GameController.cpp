#include "GameController.h"
#include "GameStateEvaluator.h"
#include "DebugLogger.h"

#include <iostream>

using namespace std;

GameController::GameController()
{
    P1 = nullptr;
    P2 = nullptr;
    BoardEntity = nullptr;
}

GameController::GameController(Player * _p1, Player * _p2) : GameController()
{
    P1 = _p1;
    P2 = _p2;
    BoardEntity = new Board(7, 6, 4);   //Default state

    numMoves = 0;
    terminatingMoveCount = BoardEntity->NumRow * BoardEntity->NumCol;
}

Move GameController::PlayGame()
{
    //Whenever a win occurs
    //  Return the player that won: NO_MOVE for draw, P1_MOVE or P2_MOVE for win
    Move winner = NO_MOVE;
    
    //Print board
    printString(cout, 0, BoardEntity->ToString());

    while (true)
    {
        winner = RunMove(true);
        if (winner != UNFINISHED)
            return winner;

        int a;
        cout << "Number to continue: ";
        cin >> a;
        cout << endl;

        winner = RunMove(false);
        if (winner != UNFINISHED)
            return winner;

        cout << "Number to continue: ";
        cin >> a;
        cout << endl;
    }
}

inline Move GameController::RunMove(bool p1)
{
    Player* player = (p1 ? P1 : P2);
    Move p = (p1 ? P1_MOVE : P2_MOVE);

    GameStateEvaluator gse = GameStateEvaluator();
    int movePos = -1;

    //Player 1 makes a move
    player->Play(BoardEntity);
    movePos = player->GetBestMove();
    BoardEntity->MakeMove(movePos, p);
    numMoves++;
    printString(cout, 0, BoardEntity->ToString());
    //Check if win
    if (gse.CheckWin(BoardEntity, p))
    {
        return p;
    }
    else if (numMoves >= terminatingMoveCount)
    {
        return NO_MOVE;
    }
    else
    {
        return UNFINISHED;
    }
}
