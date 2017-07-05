#include "GameController.h"
#include "GameStateEvaluator.h"
#include "DebugLogger.h"
#include "SocketHelper.h"
#include "AlphaBetaAI.h"
#include "IterativeDeepenAI.h"

#include <iostream>
#include <thread>
#include <typeinfo>

using namespace std;

GameController::GameController()
{
    P1 = nullptr;
    P2 = nullptr;
    NetworkedGame = false;
    BoardEntity = nullptr;
    hasWon = false;
    winningPlayer = UNFINISHED;
}

void GameController::UpdateNetworkedPlayer(bool p1)
{
    if (!NetworkedGame)
        return;

    if (hasWon)
    {
        connection.sendMessage("-1");
        std::this_thread::sleep_for(200ms);
        connection.sendMessage(to_string(winningPlayer));
        std::this_thread::sleep_for(200ms);
    }

    if (P1IsNetworked && p1)
    {
        connection.sendMessage(to_string(BoardEntity->MoveCol+1));
    }
    else if (!P1IsNetworked && !p1)
    {
        connection.sendMessage(to_string(BoardEntity->MoveCol+1));
    }
}

GameController::GameController(Player * _p1, Player * _p2, bool _NetworkGame, int _port) : GameController()
{
    P1 = _p1;
    P2 = _p2;
    NetworkedGame = _NetworkGame;
    Port = _port;
    P1IsNetworked = true;
    BoardEntity = new Board(6, 7, 4);   //Default state

    numMoves = 0;
    terminatingMoveCount = BoardEntity->NumRow * BoardEntity->NumCol;
	printString(std::cout, 0, "Player 1: " + string(typeid(*_p1).name())+"\n");
	printString(std::cout, 0, "Player 2: " + string(typeid(*_p2).name()) + "\n");
}

GameController::GameController(Player * _p1, Player * _p2, int nRows, int nCols, bool _NetworkGame, int _port)
	: GameController(_p1, _p2, _NetworkGame, _port)
{
	delete BoardEntity;
	BoardEntity = new Board(nRows, nCols, 4);
}

Move GameController::PlayGame()
{
    //Whenever a win occurs
    //  Return the player that won: NO_MOVE for draw, P1_MOVE or P2_MOVE for win
    Move winner = NO_MOVE;
    
    if (NetworkedGame)  //Wait for connection
    {
        printString(std::cout, 0, "Waiting for connection on port: " + to_string(Port) + "\n");
        Init(to_string(Port));
    }

    //Print board
    printString(cout, 0, BoardEntity->ToString());

    while (true)
    {
		cerr << "Player1 going" << endl;
        winner = RunMove(true);
        if (winner != UNFINISHED)
        {
            hasWon = true;
            winningPlayer = winner;
            UpdateNetworkedPlayer(true);
            return winner;
        }
		cerr << "Player 2 going" << endl;
        winner = RunMove(false);
        if (winner != UNFINISHED)
        {
            hasWon = true;
            winningPlayer = winner;
            UpdateNetworkedPlayer(true);
            return winner;
        }

        UpdateNetworkedPlayer(true);
    }
}

inline Move GameController::RunMove(bool p1)
{
    Player* player = (p1 ? P1 : P2);
    Move p = (p1 ? P1_MOVE : P2_MOVE);

    GameStateEvaluator gse = GameStateEvaluator();
    int movePos = -1;

    //Player 1/2 makes a move
    player->Play(BoardEntity);
    movePos = player->GetBestMove();
    BoardEntity->MakeMove(movePos, p);
    numMoves++;
    printString(cout, 0, BoardEntity->ToString());

	//Find utility from both/either/none of the AIs
	if (typeid(*player) == typeid(AlphaBetaAI) || typeid(*player) == typeid(IterativeDeepenAI)) {
		//Very bad don't do this. Only works because BestUtility is always compiled/declared in the same order
		AlphaBetaAI* tmpCast = static_cast<AlphaBetaAI*>(player);
		printString(cout, 0, "Utility: " + to_string(tmpCast->BestUtility) + "\n");
	}

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
