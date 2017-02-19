#pragma once

#include "Board.h"

/// <summary>
/// Will eventually be spawned as a new thread.
/// Abstract interface defines all functions required for a player to run
/// </summary>
class Player
{
protected:
    Board* CopyOfGame;

    int BestMove;

public:
    Player();
    
    /// <summary>
    /// Gets the best move.
    /// 
    /// </summary>
    /// <returns></returns>
    virtual int GetBestMove() = 0;
    
    /// <summary>
    /// Chooses the column to play into
    /// Must populate BestMove before move timer expires
    /// </summary>
    /// <param name="CurrentBoard">The current board.</param>
    virtual void Play(Board* CurrentBoard) = 0;
};