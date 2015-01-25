
//
//  Triangle.cpp
//  Sedimental Storm
//
//  Created by Jacob Cohen on 1/20/15.
//  Copyright (c) 2015 Jacob Cohen. All rights reserved.
//

#include "ConcaveTriangle.h"

ConcaveTriangle::ConcaveTriangle() {
    setPointCount(9);
    setPoint(0, sf::Vector2f(0, 100));
    setPoint(1, sf::Vector2f(100, 0));
    setPoint(2, sf::Vector2f(50, 0));
    setPoint(3, sf::Vector2f(40, 20));
    setPoint(4, sf::Vector2f(30, 0));
    setPoint(5, sf::Vector2f(0, 0));
    setPoint(6, sf::Vector2f(0, 30));
    setPoint(7, sf::Vector2f(20, 40));
    setPoint(8, sf::Vector2f(0, 50));
    setFillColor(sf::Color::Green);
}

void ConcaveTriangle::update() {
    rotate(0.5);
}

void ConcaveTriangle::draw(sf::RenderTarget& window, sf::RenderStates& renderState) {
    window.draw(*this, renderState);
}

