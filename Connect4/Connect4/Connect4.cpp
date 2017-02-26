// Connect4.cpp : Defines the entry point for the console application.
//

#include "Player.h"
#include "HumanPlayer.h"
#include "AlphaBetaAI.h"
#include "GameController.h"

#include<iostream>

using namespace std;

int Run()
{
    Player* p1 = new AlphaBetaAI(P1_MOVE);
    Player* p2 = new AlphaBetaAI(P2_MOVE);

    GameController gameRunner = GameController(p1, p2);

    Move winner = gameRunner.PlayGame();

    cout << "Winner was: " << winner << endl;
    return winner;
}

