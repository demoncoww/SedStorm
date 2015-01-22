#ifndef _GAMEMANAGER
#define _GAMEMANAGER
// SFML includes
//#include <SFML/System.hpp>
//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
// Box2D includes
//#include <Box2D/Box2D.h>
// Thor includes
//#include <Thor/Animations.hpp>
//#include <Thor/Config.hpp>
//#include <Thor/Graphics.hpp>
//#include <Thor/Input.hpp>
//#include <Thor/Math.hpp>
//#include <Thor/Particles.hpp>
//#include <Thor/Shapes.hpp>
//#include <Thor/Time.hpp>
//#include <Thor/Vectors.hpp>

#include "RenderManager.h"
#include "PhysicsManager.h"

class GameManager
{
private:
	// MessageManager* messageManger;
	// ResourceManager* resourceManager;
	// InputManager* inputManager;
	// GameObjectManager* gameObjectManager;
	// LevelManager* levelManager;
	PhysicsManager* physicsManager;
	RenderManager* renderManager;

	sf::RenderWindow* gameWindow;
public:
	GameManager();
	~GameManager();

	void InitInstance(void);
	void MainLoop(void);
	void Shutdown(void);
};
#endif // _GAMEMANAGER
