#include "Game.h"

// Including X server stuff if we're running linux
//#ifndef __linux__
	#include <X11/Xlib.h>
//#endif

int main()
{
//	#ifndef __linux__
		XInitThreads();
	//#endif

    Game game;
    game.run();
    return 0;
}
