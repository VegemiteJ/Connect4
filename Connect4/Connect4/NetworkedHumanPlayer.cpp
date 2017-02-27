#include "NetworkedHumanPlayer.h"
#include "SocketHelper.h"
#include "DebugLogger.h"

NetworkedHumanPlayer::NetworkedHumanPlayer(Move _p)
{}

void NetworkedHumanPlayer::Play(Board * _CurrentBoard)
{
    printString(std::cout, 0, "Player 1 waiting to receive...\n");
    std::string move = string(connection.receiveMessage());
    printString(std::cout, 0, "Message:[" + move + "]\n");
    BestMove = stoi(move);
}

int NetworkedHumanPlayer::GetBestMove()
{
    return BestMove;
}
