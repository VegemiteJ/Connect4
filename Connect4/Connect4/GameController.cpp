#include "GameController.h"
#include "GameStateEvaluator.h"
#include "DebugLogger.h"
#include "SocketHelper.h"

#include <iostream>

using namespace std;

GameController::GameController()
{
    P1 = nullptr;
    P2 = nullptr;
    NetworkedGame = false;
    BoardEntity = nullptr;
}

void GameController::UpdateNetworkedPlayer(bool p1)
{
    if (!NetworkedGame)
        return;

    if (P1IsNetworked && p1)
    {
        connection.sendMessage(to_string(BoardEntity->MoveCol+1));
    }
    else if (!P1IsNetworked && !p1)
    {
        connection.sendMessage(to_string(BoardEntity->MoveCol+1));
    }
}

GameController::GameController(Player * _p1, Player * _p2, bool _NetworkGame) : GameController()
{
    P1 = _p1;
    P2 = _p2;
    NetworkedGame = _NetworkGame;
    P1IsNetworked = true;
    BoardEntity = new Board(7, 6, 4);   //Default state

    numMoves = 0;
    terminatingMoveCount = BoardEntity->NumRow * BoardEntity->NumCol;
}

Move GameController::PlayGame()
{
    //Whenever a win occurs
    //  Return the player that won: NO_MOVE for draw, P1_MOVE or P2_MOVE for win
    Move winner = NO_MOVE;
    
    if (NetworkedGame)  //Wait for connection
    {
        printString(std::cout, 0, "Waiting for connection on port: " + string(DEFAULT_PORT) + "\n");
        Init(DEFAULT_PORT);
    }

    //Print board
    printString(cout, 0, BoardEntity->ToString());

    while (true)
    {
        winner = RunMove(true);
        if (winner != UNFINISHED)
            return winner;

        winner = RunMove(false);
        if (winner != UNFINISHED)
            return winner;

        UpdateNetworkedPlayer(true);
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
