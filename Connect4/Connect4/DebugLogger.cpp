#include "DebugLogger.h"

void printString(ostream & out, int debugLevel, string message)
{
    if (debugLevel <= DEBUG_LVL)
    {
        out << message;
    }
}
