#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// #include "includes.h" 
// #include "game.h"

// not enough helper functions to justify a header file

void clearTerminal()
{
#ifdef __APPLE__
    std::system("clear");

#else
    std::system("cls");

#endif
}

#endif
