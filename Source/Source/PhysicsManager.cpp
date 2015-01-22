#include "PhysicsManager.h"

PhysicsManager::PhysicsManager()
{
	b2Vec2 gravity(0.0f, -9.8f);
	world = new b2World(gravity);
}

PhysicsManager::~PhysicsManager()
{
	delete world; // also deletes all joints and bodies in the world
}

void PhysicsManager::InitInstance()
{
}

void PhysicsManager::Update()
{
	const float FRAMETIME = 1.0f / 60; // target number of seconds per frame
	const int32 velocityIterations = 8;   //how strongly to correct velocity
	const int32 positionIterations = 3;   //how strongly to correct position
	world->Step(FRAMETIME, velocityIterations, positionIterations);
}
