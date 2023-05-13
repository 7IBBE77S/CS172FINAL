#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// #include "includes.h" 
// #include "game.h"

// not enough helper functions to justify a header file

void clearTerminal()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	system("cls");
#elif __APPLE__
	system("clear");
#elif __linux__
	system("clear");
#endif
}
#endif
