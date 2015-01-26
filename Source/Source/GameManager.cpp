#include "GameManager.h"

//UNCOMMENT THE FOLLOWING LINE TO ENABLE PHYSICS DEBUG
#define PHYSICS_DEBUG

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
	physicsManager->InitInstance();
    
    renderManager->SetGameWindow(gameWindow);
    renderManager->SetPhysicsManager(physicsManager);
    renderManager->SetGameObjectManager(gameObjectManager);
    renderManager->InitInstance();
    
	std::string name = "game";
	GameLayer* layer = gameObjectManager->CreateGameLayer(name, true, true);

    //// Insert test triangle into the gameObjectManager
    //Triangle* triangle1 = new Triangle;
    //triangle1->setPosition(sf::Vector2f(400, 300));
    //triangle1->setFillColor(sf::Color::Green);

    //Triangle* triangle2 = new Triangle;
    ////triangle2->rotate(10);
    //triangle2->setPosition(triangle2->getPosition() + sf::Vector2f(20, 20));
    //triangle2->setFillColor(sf::Color(250, 100, 50));
    //triangle2->setParent(triangle1);

    //Triangle* triangle3 = new Triangle;
    ////triangle3->rotate(10);
    //triangle3->setPosition(triangle3->getPosition() + sf::Vector2f(20, 20));
    //triangle3->setFillColor(sf::Color(50, 100, 250));
    //triangle3->setParent(triangle2);

    //Triangle* triangle4 = new Triangle;
    ////triangle4->rotate(10);
    //triangle4->setPosition(triangle4->getPosition() + sf::Vector2f(20, 20));
    //triangle4->setFillColor(sf::Color(150, 150, 150));
    //triangle4->setParent(triangle3);

    //layer->objects.push_back(triangle2);
    //layer->objects.push_back(triangle3);
    //layer->objects.push_back(triangle4);

    //Triangle* triangle1 = new Triangle;
    //triangle1->setPosition(sf::Vector2f(400, 300));
    //triangle1->setFillColor(sf::Color::Green);

    //physicsManager->AddShapeToWorld(*triangle1);
    //layer->objects.push_back(triangle1);

#ifdef PHYSICS_DEBUG
    //ENABLE DEBUG
	physicsManager->EnableDebug(gameWindow);
#endif
    
    //Insert test triangle into the gameObjectManager
    layer->objects.push_back(new Triangle());
    layer->objects.push_back(new TestPhysicsObject(sf::Vector2f(300, 300), true));
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