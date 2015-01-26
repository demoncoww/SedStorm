#ifndef _RENDERMANAGER
#define _RENDERMANAGER
#include <SFML/Graphics.hpp>
#include <Thor/Shapes.hpp>
#include "PhysicsManager.h"
#include "GameObjectManager.h"

class RenderManager
{
private:
	sf::RenderWindow* gameWindow;
    PhysicsManager* physicsManager;
    GameObjectManager* gameObjectManager;

public:
	RenderManager();
	~RenderManager();

    void SetPhysicsManager(PhysicsManager* thePhysicsManager);
    void SetGameObjectManager(GameObjectManager* theGameObjectManager);
	void SetGameWindow(sf::RenderWindow* theGameWindow);
	void InitInstance(void);
	void Draw();
};
#endif // _RENDERMANAGER
