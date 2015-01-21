#include "GameManager.h"

GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

void GameManager::InitInstance()
{
	gameWindow.create(sf::VideoMode(800, 600), "Sedimental Storm");
	gameWindow.setVerticalSyncEnabled(true);

	sf::CircleShape circleShape(100.f);
	circleShape.setFillColor(sf::Color::Green);
	testShape = thor::ConcaveShape(circleShape);
	testShape.setOutlineThickness(1.0);
}

void GameManager::MainLoop()
{
	while (gameWindow.isOpen()) {
		sf::Event event;
		while (gameWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				gameWindow.close();
			// send event to eventmanager (keyboard, gamepad stuff)
		}

		gameWindow.clear();
		gameWindow.draw(testShape);
		gameWindow.display();
	}
}

void GameManager::Shutdown()
{
}