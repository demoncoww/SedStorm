//
//  Layer.cpp
//  Sedimental Storm
//
//  Created by Jacob Cohen on 1/20/15.
//  Copyright (c) 2015 Jacob Cohen. All rights reserved.
//

#include "Layer.h"

//THIS SHOULD BE MOVED TO THE RENDER ONCE ITS BUILT
sf::RenderWindow Layer::window(sf::VideoMode(200, 200), "SFML works!");

Layer::Layer(): objects(0), _isVisible(true), _isActive(true)
{}

Layer::Layer(bool isVisible, bool isActive): objects(0), _isVisible(isVisible), _isActive(isActive)
{}

void Layer::updateObjects(){
    for(int i=0; i<objects.size(); i++){
        objects[i]->update();
    }
}

void Layer::drawObjects(){
    for(int i=0; i<objects.size(); i++){
        objects[i]->draw(Layer::window);
    }
}

Layer::~Layer(){
    for(int i=0; i<objects.size(); i++){
        delete objects[i];
    }
}