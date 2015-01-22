
// Game includes
#include "GameManager.h"

void RedirectIOToConsole(void);
int main(int argc, char *argv[]) {
    //sf::Texture texture;
    //thor::ParticleSystem system;
    //system.setTexture(texture);
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