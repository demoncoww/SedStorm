#include "PhysicsManager.h"

b2World* PhysicsManager::world;
std::vector<PhysicsBody*> PhysicsManager::bodies;

PhysicsManager::PhysicsManager()
{
	b2Vec2 gravity(0.0f, 9.8f); //Should be 9.8
	world = new b2World(gravity);
}

PhysicsManager::~PhysicsManager()
{
	delete world; // also deletes all joints and bodies in the world
}

void PhysicsManager::InitInstance()
{
}

void PhysicsManager::EnableDebug(sf::RenderTarget* target){
    if(debugDrawer == nullptr){
        debugDrawer = new PhysicsDebugDraw(target);
        world->SetDebugDraw( debugDrawer );
    }else{
        debugDrawer->SetTarget(target);
    }
}

void PhysicsManager::Update()
{
	const float FRAMETIME = 1.0f / 60; // target number of seconds per frame
	const int32 velocityIterations = 8;   //how strongly to correct velocity
	const int32 positionIterations = 3;   //how strongly to correct position
    
    //debugDrawer->GetTarget()->clear();
   // world->DrawDebugData();
    //dynamic_cast<sf::RenderWindow*>(debugDrawer->GetTarget())->display();
    
	world->Step(FRAMETIME, velocityIterations, positionIterations);
    for(unsigned int i=0; i<bodies.size(); ++i){
        bodies[i]->UpdateParentTransform();
    }
}

PhysicsBody* PhysicsManager::AddShape(PhysicsObject& shapeOwner, sf::Shape& shape){
    PhysicsBody* physicsBody = new PhysicsBody();
    physicsBody->parent = &shapeOwner;
    
    //PhysicsObjects can't have parents so we can use the local position alone
    const sf::Vector2f position = shapeOwner.getPosition();
    
    b2BodyDef bodyDef;
    bodyDef.type = shapeOwner.isStatic ? b2_staticBody : b2_dynamicBody;
    bodyDef.position.Set(position.x, position.y); //set the starting position
    bodyDef.angle = shapeOwner.getRotation(); //set the starting angle
    
    physicsBody->body = world->CreateBody(&bodyDef);
    
    b2PolygonShape b2Shape;
    unsigned int numVerts = shape.getPointCount();
    b2Vec2 *b2Points = new b2Vec2[numVerts];
    for(unsigned int i=0; i<numVerts; ++i){
        sf::Vector2f point = shape.getPoint(i);
        b2Points[i] = b2Vec2(point.x, point.y);
    }
    
    b2Shape.Set(b2Points, numVerts);
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &b2Shape;
    fixtureDef.density = 1;
    physicsBody->body->CreateFixture(&fixtureDef);
    
    bodies.push_back(physicsBody);
    
    return physicsBody;
}
