
//
//  Triangle.cpp
//  Sedimental Storm
//
//  Created by Jacob Cohen on 1/20/15.
//  Copyright (c) 2015 Jacob Cohen. All rights reserved.
//

#include "Triangle.h"

Triangle::Triangle(){
    shape = new sf::ConvexShape();
    shape->setPointCount(3);
    shape->setPoint(2, sf::Vector2f(0,0));
    shape->setPoint(1, sf::Vector2f(100,0));
    shape->setPoint(0, sf::Vector2f(0, 100));
    shape->setPosition(300, 300);
    shape->setFillColor(sf::Color::Green);
}

void Triangle::Update(){
    shape->rotate(3);
}

void Triangle::Draw(sf::RenderWindow& window){
    window.draw(*shape);
}

