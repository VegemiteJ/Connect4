#ifndef COLOURDEF_H
#define COLOURDEF_H
//Colours for terminal printing
#if CONSOLE_MODE==1
	#define ANSI_RED "\u001B[31m"
	#define ANSI_GREEN "\u001B[32m"
	#define ANSI_RESET "\u001B[0m"
	#define ANSI_BLUE "\u001B[34m"
	#define ANSI_PURPLE "\u001B[35m"
	#define ANSI_WHITE "\u001B[37m"
	#define ANSI_CYAN "\u001B[36m"
	#define ANSI_YELLOW "\u001B[33m"
#else
	#define ANSI_RED		""
	#define ANSI_GREEN		""
	#define ANSI_RESET		""
	#define ANSI_BLUE		""
	#define ANSI_PURPLE 	""
	#define ANSI_WHITE		""
	#define ANSI_CYAN 		""
	#define ANSI_YELLOW 	""
#endif // !!CONSOLE_MODE
#endif