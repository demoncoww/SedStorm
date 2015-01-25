#include "PhysicsManager.h"

PhysicsManager::PhysicsManager()
{
	b2Vec2 gravity(0.0f, -9.8f);
	world = new b2World(gravity);
}

PhysicsManager::~PhysicsManager()
{
	delete world; // also deletes all bodies, shaopes, fixtures, and joints in the world
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

void PhysicsManager::Update()
{
	const float FRAMETIME = 1.0f / 60; // target number of seconds per frame
	const int32 velocityIterations = 8;   //how strongly to correct velocity
	const int32 positionIterations = 3;   //how strongly to correct position
	world->Step(FRAMETIME, velocityIterations, positionIterations);
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
    bodyDef.position.Set(0.0f, 4.0f);
    b2Body* body = world->CreateBody(&bodyDef);

    b2PolygonShape polygon = ShapeToPolygon(shape);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &polygon;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);
}
