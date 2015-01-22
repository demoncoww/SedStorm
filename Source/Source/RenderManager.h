#ifndef _RENDERMANAGER
#define _RENDERMANAGER
#include <SFML/Graphics.hpp>
#include <Thor/Shapes.hpp>

class RenderManager
{
private:
	thor::ConcaveShape testShape;
	sf::RenderWindow* gameWindow;

public:
	RenderManager();
	~RenderManager();

	void SetGameWindow(sf::RenderWindow* theGameWindow);
	void InitInstance(void);
	void Draw();
};
#endif // _RENDERMANAGER
