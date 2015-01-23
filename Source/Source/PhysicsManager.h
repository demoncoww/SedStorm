#ifndef _PHYSICSMANAGER
#define _PHYSICSMANAGER
#include <Box2D/Box2D.h>
#include <Thor/Shapes.hpp>

class PhysicsManager
{
private:
	b2World* world; 
public:
	PhysicsManager();
	~PhysicsManager();

	void InitInstance(void);
	void Update(void);
	// takes a ConcaveShape, splits it into multiple fixtures
	// creates a body for the fixtures, and places the body in the world
	// http://www.emanueleferonato.com/2011/09/12/create-non-convex-complex-shapes-with-box2d/
	void AddConcaveShape(thor::ConcaveShape shape);
	// returns true if a polygon is concave
	bool IsConcave(thor::ConcaveShape shape);
	// returns true if a polygon is complex (crossing lines or a hole)
	bool IsComplex(thor::ConcaveShape shape);
	// we need functions for: splitting a complex polygon into simple polygons
	// http://stackoverflow.com/questions/4001745/testing-whether-a-polygon-is-simple-or-complex
	// we also need a function to slice concave polygons
	// http://www.emanueleferonato.com/2011/08/05/slicing-splitting-and-cutting-objects-with-box2d-part-4-using-real-graphics/
};
#endif // _PHYSICSMANAGER
