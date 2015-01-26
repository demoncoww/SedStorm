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
			objects[i]->Draw(window, renderState); // draw parent
            renderState.transform *= objects[i]->getTransform(); // apply parents transform before sending to children
			DrawChildren(window, objects[i], renderState); // send window, parent, and parent transformation
		}
    }
}

void Layer::DrawChildren(sf::RenderTarget& target, GameObject* parent, sf::RenderStates& renderState) {
	for (auto& child : parent->GetChildren()) {
		child->Draw(target, renderState); // draw child
        sf::Transform oldTransform = renderState.transform; // save transform
        renderState.transform *= child->getTransform(); // apply childs's tranform before sending to next child
		DrawChildren(target, child, renderState);
        renderState.transform = oldTransform; // restore transform in case there are more than one child
	}
}

Layer::~Layer(){
    for(unsigned int i=0; i<objects.size(); i++){
        delete objects[i];
    }
}