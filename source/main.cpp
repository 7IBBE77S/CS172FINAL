/************************************************************
*  Author:         Nicholas Tibbetts
*  Date:           12/06/2022 T09:33:37
*  Course Code:    CS-172-2
*  License:        Copyright 2022 Nic Tibbetts
*  Resources used: 
                   https://cplusplus.com/
                   https://en.cppreference.com/w/cpp/17
                   https://en.cppreference.com/w/cpp/types/size_t
                   https://en.cppreference.com/w/cpp/language/static_cast
                   https://en.cppreference.com/w/cpp/language/virtual
				   https://cplusplus.com/reference/sstream/stringstream/
				   https://en.cppreference.com/w/cpp/language/inline

                   
*  Work cited (inspiration): https://github.com/7IBBE77S/Go/tree/main/Monster%20Game 
							 https://www.youtube.com/watch?v=NcdgNIb3pYU
							 https://www.youtube.com/watch?v=ssJde6l7mrM&list=RDCMUC4EJN2OSNdl-mSxGjitRvyA&start_radio=1&rv=ssJde6l7mrM&t=1562
							 https://www.youtube.com/@javidx9
*  Worked with:    _
*  Description:    Basic "RPG" terminal game.
***********************************************************/

#include "game.h"
int main ()
{
	// initialize random number generator to current time
	srand(time(NULL));


	Game game;

	game.clearTerminal();
	game.startGame();

	for (game.isPlaying(); game.isPlaying();)
	{
		game.mainMenu();
	}

	return 0;
}