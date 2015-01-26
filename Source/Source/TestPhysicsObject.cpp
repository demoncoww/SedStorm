//
//  TestPhysicsObject.cpp
//  Sedimental Storm
//
//  Created by Jacob Cohen on 1/22/15.
//  Copyright (c) 2015 Jacob Cohen. All rights reserved.
//

#include "TestPhysicsObject.h"

TestPhysicsObject::TestPhysicsObject():PhysicsObject(){
    setPointCount(3);
    setPoint(0, sf::Vector2f(0, 20));
    setPoint(1, sf::Vector2f(20, -20));
    setPoint(2, sf::Vector2f(-20, -20));
    //setPosition(300, 300);
    setFillColor(sf::Color::Red);
    
    setPosition(300, 300);
    
    isStatic = false;
    
    PhysicsManager::AddShape(*this);
}

TestPhysicsObject::TestPhysicsObject(sf::Vector2f position, bool isStatic):PhysicsObject(){
    setPointCount(3);
    setPoint(0, sf::Vector2f(0, 10));
    setPoint(1, sf::Vector2f(5, -5));
    setPoint(2, sf::Vector2f(-5, -5));
    //setPosition(0,0);
    setFillColor(sf::Color::Red);
    
    setPosition(position);
    setRotation(90);

    this->isStatic = isStatic;
    
    PhysicsManager::AddShape(*this);
}

void TestPhysicsObject::Update(){
    //rotate(6);
}

void TestPhysicsObject::Draw(sf::RenderTarget& window, sf::RenderStates& renderState)
{
    window.draw(*this, renderState);
}



