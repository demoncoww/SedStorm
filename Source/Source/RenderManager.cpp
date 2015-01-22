#include "RenderManager.h"

RenderManager::RenderManager()
{
}

RenderManager::~RenderManager()
{
}

void RenderManager::InitInstance()
{
}

void RenderManager::SetGameWindow(sf::RenderWindow* theGameWindow)
{
	gameWindow = theGameWindow;
}

void RenderManager::SetGameObjectManager(GameObjectManager* theGameObjectManager){
    gameObjectManager = theGameObjectManager;
}

void RenderManager::Draw()
{
	gameWindow->clear();
    gameObjectManager->drawLayers(*gameWindow);
	gameWindow->display();
}
