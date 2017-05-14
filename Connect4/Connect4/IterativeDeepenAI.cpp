#include "IterativeDeepenAI.h"
#include "DebugLogger.h"

#include <thread>
#include <chrono>
#include <cmath>

IterativeDeepenAI::IterativeDeepenAI(Move _p) : ai(AlphaBetaAI(_p))
{
    startDepth = 4;
    p = _p;
}

IterativeDeepenAI::IterativeDeepenAI(Move _p, int _startDepth) : IterativeDeepenAI(_p)
{
    startDepth = _startDepth;
}

void IterativeDeepenAI::Play(Board * _CurrentBoard)
{
    using namespace std::chrono;
    //Start time measurement
    high_resolution_clock::time_point t1 = high_resolution_clock::now();    

    //Reset Conditions:
    int backupCol = _CurrentBoard->MoveCol;
    int backupRow = _CurrentBoard->MoveRow;
    Move backupMove = _CurrentBoard->LastMove;

    //While computation time remaining
    //  AB search from startDepth++ each iteration
    high_resolution_clock::time_point runStart;
    high_resolution_clock::time_point runEnd;
    int itr = startDepth;
    double realDuration = 0.0;
    double calculationTime = 2.0;
    double timeRemaining = calculationTime;
    int numberPossible = _CurrentBoard->NumCol * _CurrentBoard->NumRow;
    //Do a model whereby roughly if 5*LastRunTime < durationRemaining, run a search
    while (3*realDuration < timeRemaining && (itr + _CurrentBoard->NumMovesTotal)<=numberPossible)
    {
        printString(std::cout, 1, "\nRunning for Depth " + to_string(itr) + "\n");
        ai.MaxDepth = itr;

        runStart = high_resolution_clock::now();
        ai.Play(_CurrentBoard);
        runEnd = high_resolution_clock::now();
        auto runDuration = duration_cast<milliseconds>(runEnd - runStart).count();
        realDuration = ((double)runDuration) / 1000.0;

        BestUtility = ai.BestUtility;
        BestMove = ai.GetBestMove();

        printString(std::cout, 1, "\tUtility: " + to_string(BestUtility) + "\n");
        printString(std::cout, 1, "\tBestMove: " + to_string(BestMove) + "\n");
        printString(std::cout, 1, "\tCalculated to depth " + to_string(itr) + " in: " + to_string(realDuration) + "s\n");
        itr++;

        //Resetting
        ai.Reset();
        _CurrentBoard->MoveCol = backupCol;
        _CurrentBoard->MoveRow = backupRow;
        _CurrentBoard->LastMove = backupMove;

        //Calculate if enough time remaining
        //  Do a model whereby roughly if 5*LastRunTime < durationRemaining, run a search
        auto durationSoFar = duration_cast<milliseconds>(runEnd - t1).count();
        double realDurationSoFar = ((double)durationSoFar) / 1000.0;
        timeRemaining = calculationTime - realDurationSoFar;
        printString(std::cout, 1, "\tElapsed " + to_string(realDurationSoFar) + "s Remaining: " + to_string(timeRemaining) + "s\n");
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(t2 - t1).count();

    printString(std::cout, 1, "\tCalculated to depth " + to_string(itr-1) + " in: " + to_string((double)duration/1000.0) + "s\n");
}

int IterativeDeepenAI::GetBestMove()
{
    return BestMove;
}

/// <summary>
/// Using fitted exponential model - predict the execution time
/// </summary>
/// <param name="numCols">The number cols.</param>
/// <param name="depth">The depth.</param>
/// <returns></returns>
double IterativeDeepenAI::ExpectedTime(int numCols, int depth)
{
    double nC = (double)numCols;
    double d = (double)depth;

    double a = 0.1;
    double b = 0.2898;

    double expectedSeconds = a*(pow(b*nC, d));
    return expectedSeconds;
}