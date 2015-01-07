// SFML includes
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
// Box2D includes
#include <Box2D\Box2D.h>
// Thor includes
#include <Thor\Animations.hpp>
#include <Thor\Config.hpp>
#include <Thor\Graphics.hpp>
#include <Thor\Input.hpp>
#include <Thor\Math.hpp>
#include <Thor\Particles.hpp>
#include <Thor\Shapes.hpp>
#include <Thor\Time.hpp>
#include <Thor\Vectors.hpp>

#ifdef _MSC_VER
// Visual Studio specific stuff here
#endif

int main(int argc, char *argv[]) {
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);

    sf::Texture texture;
    thor::ParticleSystem system;
    system.setTexture(texture);

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}