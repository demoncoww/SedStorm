//
//  TestPhysicsObject.cpp
//  Sedimental Storm
//
//  Created by Jacob Cohen on 1/22/15.
//  Copyright (c) 2015 Jacob Cohen. All rights reserved.
//

#include "TestPhysicsObject.h"

TestPhysicsObject::TestPhysicsObject():PhysicsObject(){
    shape = new sf::ConvexShape();
    shape->setPointCount(3);
    shape->setPoint(0, sf::Vector2f(0, 20));
    shape->setPoint(1, sf::Vector2f(20, -20));
    shape->setPoint(2, sf::Vector2f(-20, -20));
    //shape->setPosition(300, 300);
    shape->setFillColor(sf::Color::Red);
    
    setPosition(300, 300);
    
    isStatic = false;
    
    PhysicsManager::AddShape(*this, *shape);
}

//NOTE PHYSICS IS Not ALL FUCKED UP anymore
TestPhysicsObject::TestPhysicsObject(sf::Vector2f position, bool isStatic):PhysicsObject(){
    shape = new sf::ConvexShape();
    shape->setPointCount(3);
    shape->setPoint(0, sf::Vector2f(0, 10));
    shape->setPoint(1, sf::Vector2f(5, -5));
    shape->setPoint(2, sf::Vector2f(-5, -5));
    //shape->setPosition(0,0);
    shape->setFillColor(sf::Color::Red);
    
    setPosition(position);
    setRotation(90);

    this->isStatic = isStatic;
    
    PhysicsManager::AddShape(*this, *shape);
}

void TestPhysicsObject::Update(){
    //shape->rotate(6);
}

void TestPhysicsObject::Draw(sf::RenderTarget& window, sf::RenderStates& renderState)
{
    window.draw(*shape, renderState);
}



