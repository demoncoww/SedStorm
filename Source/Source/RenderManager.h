#ifndef _RENDERMANAGER
#define _RENDERMANAGER
#include <SFML/Graphics.hpp>
#include <Thor/Shapes.hpp>
#include "GameObjectManager.h"

class RenderManager
{
private:
	sf::RenderWindow* gameWindow;
    GameObjectManager* gameObjectManager;

public:
	RenderManager();
	~RenderManager();

    void SetGameObjectManager(GameObjectManager* theGameObjectManager);
	void SetGameWindow(sf::RenderWindow* theGameWindow);
	void InitInstance(void);
	void Draw();
};
#endif // _RENDERMANAGER
