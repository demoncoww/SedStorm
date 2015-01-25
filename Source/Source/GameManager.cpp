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
    
    physicsManager->EnableDebug(gameWindow);
    
    //Insert test triangle into the gameObjectManager
    std::string name = "game";
    GameLayer* layer = gameObjectManager->CreateGameLayer(name, true, true);
    layer->objects.push_back(new Triangle());
    layer->objects.push_back(new TestPhysicsObject(sf::Vector2f(300,300), true));
    layer->objects.push_back(new TestPhysicsObject(sf::Vector2f(300,0), false));
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
            gameObjectManager->UpdateLayers();
            
            // render scene
			renderManager->Draw();
			physicsManager->Update();
		}
	}
}

void GameManager::Shutdown()
{
}