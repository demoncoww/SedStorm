
//
//  Triangle.cpp
//  Sedimental Storm
//
//  Created by Jacob Cohen on 1/20/15.
//  Copyright (c) 2015 Jacob Cohen. All rights reserved.
//

#include "Triangle.h"

Triangle::Triangle(){
    setPointCount(3);
    setPoint(0, sf::Vector2f(0, 100));
    setPoint(1, sf::Vector2f(100, 0));
    setPoint(2, sf::Vector2f(0, 0));
    setFillColor(sf::Color::Green);
}

void Triangle::update() {
    rotate(0.5);
}

void Triangle::draw(sf::RenderTarget& window, sf::RenderStates& renderState) {
    window.draw(*this, renderState);
}
