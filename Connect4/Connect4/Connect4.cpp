// Connect4.cpp : Defines the entry point for the console application.

#include "Player.h"
#include "HumanPlayer.h"
#include "NetworkedHumanPlayer.h"
#include "AlphaBetaAI.h"
#include "IterativeDeepenAI.h"
#include "GameController.h"

#include "DebugLogger.h"

#include<iostream>

using namespace std;

int Run(int debugLvl, int port)
{

    Player* p1 = new NetworkedHumanPlayer(P1_MOVE);
    //Player* p1 = new IterativeDeepenAI(P1_MOVE, 4);
    Player* p2 = new IterativeDeepenAI(P2_MOVE, 4);

    DEBUG_LVL = debugLvl;
    GameController gameRunner = GameController(p1, p2, true, port);

    Move winner = gameRunner.PlayGame();
    string winnerStr = (winner == P1_MOVE ? "P1" : (winner == P2_MOVE ? "P2" : "DRAW"));
    cout << "Winner was: " << winnerStr << endl;

    delete p1;
    delete p2;
    
    return winner;
}