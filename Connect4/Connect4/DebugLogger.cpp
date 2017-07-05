#include "DebugLogger.h"

int DEBUG_LVL = 1;

void printString(ostream & out, int debugLevel, string message)
{
    if (debugLevel <= DEBUG_LVL)
    {
        out << message;
    }
}

void printString(ostream & out, int debugLevel, int indentLvl, string message)
{
	if (debugLevel <= DEBUG_LVL)
	{
		for (int i = 0; i < indentLvl; i++) {
			out << "\t";
		}
		out << message;
	}
}
