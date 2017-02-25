#include "GameController.h"
#include "GameStateEvaluator.h"

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

    while (true)
    {
        //Print board
        cout << BoardEntity->ToString() << endl;

        winner = RunMove(true);
        if (winner != UNFINISHED)
            return winner;

        winner = RunMove(false);
        if (winner != UNFINISHED)
            return winner;
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
    cout << BoardEntity->ToString() << endl;
    //Check if win
    if (gse.CheckWin(BoardEntity, P1_MOVE))
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
