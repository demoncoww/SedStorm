#ifndef _PHYSICSMANAGER
#define _PHYSICSMANAGER
#include <Box2D/Box2D.h>
#include <Thor/Shapes.hpp>
#include <Thor/Math.hpp>
#include <vector>
#include "PhysicsBody.h"
#include "PhysicsObject.h"
#include "PhysicsDebugDraw.h"

class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager();

    void InitInstance(void);
	void Update(void);
    void EnableDebug(sf::RenderTarget* target);
    static PhysicsBody* AddShape(PhysicsObject& shapeOwner, sf::Shape& shape);
	// takes a ConcaveShape, splits it into multiple fixtures
	// creates a body for the fixtures, and places the body in the world
	// http://www.emanueleferonato.com/2011/09/12/create-non-convex-complex-shapes-with-box2d/
    static PhysicsBody* AddConcaveShape(PhysicsObject& shapeOwner, thor::ConcaveShape& shape);
	// returns true if a polygon is concave
	bool IsConcave(thor::ConcaveShape shape);
	// returns true if a polygon is complex (crossing lines or a hole)
	// http://stackoverflow.com/questions/4001745/testing-whether-a-polygon-is-simple-or-complex
	bool IsComplex(thor::ConcaveShape shape);
	// we need functions for: splitting a complex polygon into simple polygons
	// we also need a function to slice concave polygons
	// http://www.emanueleferonato.com/2011/08/05/slicing-splitting-and-cutting-objects-with-box2d-part-4-using-real-graphics/

    // converts a SFML shape into a Box2D polygon shape
    b2PolygonShape ShapeToPolygon(const sf::ConvexShape& shape);
    // adds a SFML shape to the current world, creating a body and fixture for it first
    void AddShapeToWorld(const sf::ConvexShape& shape);
    
private:
    PhysicsDebugDraw* debugDrawer;
    static b2World* world;
    static std::vector<PhysicsBody*> bodies;
};
#endif // _PHYSICSMANAGER
