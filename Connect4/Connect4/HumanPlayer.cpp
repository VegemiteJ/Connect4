#include "HumanPlayer.h"
#include <random>
#include <iostream>

using namespace std;

bool HumanPlayer::CheckValidMove(vector<int>* possibilities, int selected)
{
    for (int i=0; i< (*possibilities).size(); i++)
    {
        if (selected == (*possibilities)[i])
            return true;
    }
    return false;
}

HumanPlayer::HumanPlayer() : Player() {}

HumanPlayer::HumanPlayer(int _position) : Player()
{
    position = _position;
}

int HumanPlayer::GetBestMove()
{
    return BestMove;
}

void HumanPlayer::Play(Board* CurrentBoard)
{
    //Generate a random move
    CopyOfGame = CurrentBoard;
    vector<int>* validMoves = CopyOfGame->GetAllValidMoves();

    default_random_engine generator;
    uniform_int_distribution<int> distribution(0, validMoves->size()-1);
    int move = distribution(generator);
    BestMove = (*validMoves)[move];

    //Notify the player for a move
    int selectedMove = -1;
    while (!CheckValidMove(validMoves, selectedMove-1))
    {
        string input;
        cout << "Type a Column(1,NumCol): " << endl;
        cin >> input;
        try 
        {
            selectedMove = stoi(input);
        }
        catch (exception ex)
        {
            selectedMove = -1;
        }
    }

    BestMove = selectedMove;
}
