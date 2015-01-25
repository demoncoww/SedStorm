//
//  Layer.cpp
//  Sedimental Storm
//
//  Created by Jacob Cohen on 1/20/15.
//  Copyright (c) 2015 Jacob Cohen. All rights reserved.
//

#include "Layer.h"

Layer::Layer(): objects(0), isVisible(true), isActive(true)
{}

Layer::Layer(bool isVisible, bool isActive): objects(0), isVisible(isVisible), isActive(isActive)
{}

void Layer::UpdateObjects(){
    for(unsigned int i=0; i<objects.size(); i++){
        objects[i]->Update();
    }
}

void Layer::DrawObjects(sf::RenderWindow& window) {
    for(unsigned int i=0; i<objects.size(); i++){
		if (objects[i]->IsTopLevel()) {
			sf::RenderStates renderState = sf::RenderStates::Default; // identity matrix
            renderState.transform *= objects[i]->getTransform(); // as we are doing this here, make sure that any derived draw() functions pass in a shape with an identity matrix in its Transformable
			objects[i]->Draw(window, renderState); // draw parent with its local transformation applied
			DrawChildren(window, objects[i], renderState); // send window, parent, and parent transformation
		}
    }
}

void Layer::DrawChildren(sf::RenderTarget& target, GameObject* parent, sf::RenderStates& renderState) {
	for (auto& child : parent->GetChildren()) {
        renderState.transform *= child->getTransform();
		child->Draw(target, renderState);
		DrawChildren(target, child, renderState);
	}
}

Layer::~Layer(){
    for(unsigned int i=0; i<objects.size(); i++){
        delete objects[i];
    }
}