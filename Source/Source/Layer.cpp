//
//  Layer.cpp
//  Sedimental Storm
//
//  Created by Jacob Cohen on 1/20/15.
//  Copyright (c) 2015 Jacob Cohen. All rights reserved.
//

#include "Layer.h"

Layer::Layer(): objects(0), _isVisible(true), _isActive(true)
{}

Layer::Layer(bool isVisible, bool isActive): objects(0), _isVisible(isVisible), _isActive(isActive)
{}

void Layer::updateObjects(){
    for(unsigned int i=0; i<objects.size(); i++){
        objects[i]->update();
    }
}

void Layer::drawObjects(sf::RenderWindow& window) {
    for(unsigned int i=0; i<objects.size(); i++){
		if (objects[i]->IsTopLevel()) {
			sf::RenderStates renderState = sf::RenderStates::Default;
			objects[i]->draw(window, renderState);
			renderState.transform = objects[i]->getTransform();
			DrawChildren(window, objects[i], renderState);
		}
    }
}

void Layer::DrawChildren(sf::RenderTarget& target, GameObject* parent, sf::RenderStates& renderState) {
	for (auto child : parent->getChildren()) {
		renderState.transform *= child->getTransform();
		child->draw(target, renderState);
		DrawChildren(target, child, renderState);
	}
}

Layer::~Layer(){
    for(unsigned int i=0; i<objects.size(); i++){
        delete objects[i];
    }
}