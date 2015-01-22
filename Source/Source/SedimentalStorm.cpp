

#ifdef _MSC_VER
// Visual Studio specific stuff here
#endif

#include "SedimentalStorm.h"

int main(int argc, char *argv[]) {
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);

    sf::Texture texture;
    thor::ParticleSystem system;
    system.setTexture(texture);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    GameObjectManager gmManager;
    std::string name = "game";
    GameLayer* layer = gmManager.createGameLayer(name, true, true);
    layer->objects.push_back(new Triangle());
    
    while (Layer::window.isOpen()) {
        sf::Event event;
        while (Layer::window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                Layer::window.close();
        }

        gmManager.updateLayers();
        
        Layer::window.clear();
        //window.draw(shape);
        gmManager.drawLayers();
        Layer::window.display();
    }

    return 0;
}