#include "GameManager.h"

GameManager::GameManager()
{
	gameWindow = new sf::RenderWindow;
	renderManager = new RenderManager;
	physicsManager = new PhysicsManager;
    gameObjectManager = new GameObjectManager;
}

GameManager::~GameManager()
{
	delete gameObjectManager;
	delete physicsManager;
	delete renderManager;
	delete gameWindow;
}

void GameManager::InitInstance()
{
	gameWindow->create(sf::VideoMode(800, 600, 32), "Sedimental Storm");
	renderManager->SetGameWindow(gameWindow);
    renderManager->SetGameObjectManager(gameObjectManager);
	renderManager->InitInstance();
	physicsManager->InitInstance();
    
    //Insert test triangle into the gameObjectManager
    std::string name = "game";
    GameLayer* layer = gameObjectManager->createGameLayer(name, true, true);
	Triangle* triangle1 = new Triangle;

	Triangle* triangle2 = new Triangle;
	triangle2->rotate(30);
	triangle2->setPosition(triangle2->getPosition() + sf::Vector2f(50, 50));
	triangle2->shape->setFillColor(sf::Color(250, 100, 50));
	triangle2->setParent(triangle1);

	Triangle* triangle3 = new Triangle;
	triangle3->rotate(60);
	triangle3->setPosition(triangle3->getPosition() + sf::Vector2f(25, 50));
	triangle3->shape->setFillColor(sf::Color(50, 100, 250));
	triangle3->setParent(triangle2);

	Triangle* triangle4 = new Triangle;
	triangle4->rotate(90);
	triangle4->setPosition(triangle4->getPosition() + sf::Vector2f(75, 75));
	triangle4->shape->setFillColor(sf::Color(150, 150, 150));
	triangle4->setParent(triangle3);

	layer->objects.push_back(triangle1);
	layer->objects.push_back(triangle2);
	layer->objects.push_back(triangle3);
	layer->objects.push_back(triangle4);
}

void GameManager::MainLoop()
{
	const float FRAMETIME = 1.0f / 60; // target number of seconds per frame
	sf::Clock clock; // create and start clock
	sf::Event event;
	float lastFrameTime = 0;
	float currentTime;
	float timeSinceLastUpdate = 0;
	unsigned int frame = 0; // current frame

	while (gameWindow->isOpen()) {
		while (gameWindow->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				gameWindow->close();
			// send events to eventmanager (keyboard, gamepad stuff)
		}
		//printf("Processing Messages\n");
		currentTime = clock.getElapsedTime().asSeconds();
		if (currentTime >= FRAMETIME * frame) {
			// physics simulation
			timeSinceLastUpdate = currentTime - lastFrameTime;
			if (timeSinceLastUpdate > FRAMETIME * 2.0f) {
				frame = (int)(currentTime / FRAMETIME);
				timeSinceLastUpdate = FRAMETIME;
			}
			if (timeSinceLastUpdate < FRAMETIME * 0.75f) {
				frame = (int)(currentTime / FRAMETIME);
				timeSinceLastUpdate = FRAMETIME;
			}
			++frame;
			lastFrameTime = currentTime;
			//printf("Time since last frame is %f seconds, frame %d\n", timeSinceLastUpdate, frame);
            //Run game logic:
            gameObjectManager->updateLayers();
            
            // render scene
			renderManager->Draw();
			physicsManager->Update();
		}
	}
}

void GameManager::Shutdown()
{
}