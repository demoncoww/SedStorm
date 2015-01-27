
//UNCOMMENT THE FOLLOWING LINE TO ENABLE PHYSICS DEBUG
//#define PHYSICS_DEBUG

#include "GameManager.h"
#include "SedimentalStorm.h"
#include "geometry.hpp"

void RedirectIOToConsole(void);

int main(int argc, char *argv[]) {
	GameManager game;

	#ifdef _DEBUG
		#ifdef _MSC_VER
			RedirectIOToConsole(); // create a console for debugging so that we can print out debug data (WINDOWS ONLY)
		#endif
	#endif

	game.InitInstance();
	game.MainLoop();
	game.Shutdown();
    return 0;
}