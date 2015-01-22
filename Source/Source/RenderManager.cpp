#include "RenderManager.h"

RenderManager::RenderManager()
{
}

RenderManager::~RenderManager()
{
}

void RenderManager::InitInstance()
{
	// a test shape to display
	sf::CircleShape circleShape(100.f);
	circleShape.setFillColor(sf::Color::Green);
	testShape = thor::ConcaveShape(circleShape);
	testShape.setOutlineThickness(1.0);
}

void RenderManager::SetGameWindow(sf::RenderWindow* theGameWindow)
{
	gameWindow = theGameWindow;
}

void RenderManager::Draw()
{
	gameWindow->clear();
	gameWindow->draw(testShape);
	gameWindow->display();
}
