
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
    setPoint(0, sf::Vector2f(0, 10));
    setPoint(1, sf::Vector2f(10, 0));
    setPoint(2, sf::Vector2f(5, 0));
    setPoint(3, sf::Vector2f(4, 2));
    setPoint(4, sf::Vector2f(3, 0));
    setPoint(5, sf::Vector2f(0, 0));
    setPoint(6, sf::Vector2f(0, 3));
    setPoint(7, sf::Vector2f(2, 4));
    setPoint(8, sf::Vector2f(0, 5));
    setFillColor(sf::Color::Green);
    setPosition(50, 20);
}

void ConcaveTriangle::Update() {
    rotate(0.5);
}

void ConcaveTriangle::Draw(sf::RenderTarget& window, sf::RenderStates& renderState) {
    window.draw(*this, renderState);
}

