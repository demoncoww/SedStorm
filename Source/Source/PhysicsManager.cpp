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
	delete world; // also deletes all bodies, shapes, fixtures, and joints in the world
}

void PhysicsManager::InitInstance()
{
    // create the ground body
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);
    b2Body* groundBody = world->CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);
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
    //world->DrawDebugData();
    //dynamic_cast<sf::RenderWindow*>(debugDrawer->GetTarget())->display();
    
	world->Step(FRAMETIME, velocityIterations, positionIterations);
    for(unsigned int i=0; i<bodies.size(); ++i){
        bodies[i]->UpdateParentTransform();
    }
}

PhysicsBody* PhysicsManager::AddShape(PhysicsObject& shapeOwner){
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
	unsigned int numVerts = shapeOwner.getPointCount();
	b2Vec2 *b2Points = (b2Vec2*)alloca(sizeof(b2Vec2) * numVerts);
    for(unsigned int i=0; i<numVerts; ++i){
		sf::Vector2f point = shapeOwner.getPoint(i);
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

// converts a SFML shape into a Box2D polygon shape
b2PolygonShape PhysicsManager::ShapeToPolygon(const sf::ConvexShape& shape) {
    b2PolygonShape polygon;
    int numVerts = shape.getPointCount();
    b2Vec2* vertices = (b2Vec2*)alloca(sizeof(b2Vec2) * numVerts); // allocate temp vertices on the stack
    for (unsigned int i = 0; i < shape.getPointCount(); ++i) {
        sf::Vector2f point = shape.getPoint(i);
        vertices[i].Set(point.x, point.y);
    }
    polygon.Set(vertices, numVerts);
    return polygon;
}

// adds a SFML shape to the current world, creating a body and fixture for it first
void PhysicsManager::AddShapeToWorld(const sf::ConvexShape& shape) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    sf::Vector2f pos = shape.getPosition();
    bodyDef.position.Set(pos.x, pos.y); // shapes position is relative to this
    bodyDef.angle = thor::toRadian(shape.getRotation());
    b2Body* body = world->CreateBody(&bodyDef);
    body->SetUserData(0); // store the pointer to the GameObject here

    b2PolygonShape polygon = ShapeToPolygon(shape);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &polygon;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);
}

// Box2D tutorials at http://www.iforce2d.net/b2dtut/bodies
