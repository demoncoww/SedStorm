
// Game includes
#include "GameManager.h"

int main(int argc, char *argv[]) {
    //b2Vec2 gravity(0.0f, -10.0f);
    //b2World world(gravity);

    //sf::Texture texture;
    //thor::ParticleSystem system;
    //system.setTexture(texture);
	GameManager game;

	game.InitInstance();
	game.MainLoop();
	game.Shutdown();
    return 0;
}