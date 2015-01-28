#include "GameManager.h"

// for testing
#include "Triangle.h"
#include "ConcaveTriangle.h"
#include "TestPhysicsObject.h"
#include "Sliceable.h"

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
	// logical game world coordinates are 80 by 45 meters
    gameWindow->create(sf::VideoMode(1200, 675, 32), "Sedimental Storm"); // actual size of game window
    
    sf::View view;
    view.setCenter(sf::Vector2f(40, 22.5)); // center of logical game world
    view.setSize(sf::Vector2f(80, 45)); // size of logical game world in meters (for box2D)
    gameWindow->setView(view);

	physicsManager->InitInstance();
    
    renderManager->SetGameWindow(gameWindow);
    renderManager->SetPhysicsManager(physicsManager);
    renderManager->SetGameObjectManager(gameObjectManager);
    renderManager->InitInstance();
    
	std::string name = "game";
	GameLayer* layer = gameObjectManager->CreateGameLayer(name, true, true);

#ifdef PHYSICS_DEBUG
    // Enable drawing of physics objects
	physicsManager->EnableDebug(gameWindow);
#endif
    
    // Create some test shapes
    ConcaveTriangle* triangle1 = new ConcaveTriangle();
    triangle1->setFillColor(sf::Color::Blue);
    layer->objects.push_back(triangle1);

    layer->objects.push_back(new TestPhysicsObject(sf::Vector2f(15, 30), true));
    layer->objects.push_back(new TestPhysicsObject(sf::Vector2f(12.5,0), false));
    std::vector<sf::Vector2f> points;
    points.push_back(sf::Vector2f(-2.5f, -2.5f));
    points.push_back(sf::Vector2f(-2.5f, 2.5f));
    points.push_back(sf::Vector2f(2.5f, 2.5f));
    points.push_back(sf::Vector2f(2.5f, -2.5f));
    layer->objects.push_back(new Sliceable(sf::Vector2f(16,10), points, false));
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
            gameObjectManager->UpdateLayers(); // are we sure we only want to do this only on every frame?
			// run physics simulation
            physicsManager->Update();
            // render scene
			renderManager->Draw();
		}
	}
}

void GameManager::Shutdown()
{
}