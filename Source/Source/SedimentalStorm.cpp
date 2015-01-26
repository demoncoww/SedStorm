// Game includes
#include "GameManager.h"
#include "SedimentalStorm.h"
//#include "geometry.hpp"

void RedirectIOToConsole(void);

int main(int argc, char *argv[]) {
	//b2World testworld(b2Vec2(0,-9.8f));
	//b2FixtureDef fixtureDef;
	//fixtureDef.density = 1;
	//b2BodyDef bodyDef;
	//bodyDef.type = b2_dynamicBody;
	//bodyDef.position.Set(0.0f, 0.0f);
	//bodyDef.angle = 0.0f;
	//vector<b2Vec2> vertices;
	//vertices.push_back(b2Vec2(0, 100));
	//vertices.push_back(b2Vec2(100, 0));
	//vertices.push_back(b2Vec2(50, 0));
	//vertices.push_back(b2Vec2(40, 20));
	//vertices.push_back(b2Vec2(30, 0));
	//vertices.push_back(b2Vec2(0, 0));
	//vertices.push_back(b2Vec2(0, 30));
	//vertices.push_back(b2Vec2(20, 40));
	//vertices.push_back(b2Vec2(0, 50));
	//vertices.push_back(b2Vec2(0.0f, 0.0f));

	//geometry::Separate(testworld, bodyDef, fixtureDef, vertices);

	GameManager game;

	#ifdef _DEBUG
		#ifdef _MSC_VER
			RedirectIOToConsole(); // create a console for debugging so that we can print out debug data (WINDOWS ONLY)
		#endif
	#endif

	game.InitInstance();
	game.MainLoop();
	game.Shutdown();
    return 0;
}