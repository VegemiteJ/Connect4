#include "DebugLogger.h"

int DEBUG_LVL = 0;

void printString(ostream & out, int debugLevel, string message)
{
    if (debugLevel <= DEBUG_LVL)
    {
        out << message;
    }
}
