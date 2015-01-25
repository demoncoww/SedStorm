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
    shape->setPoint(2, sf::Vector2f(0,0));
    shape->setPoint(1, sf::Vector2f(100,0));
    shape->setPoint(0, sf::Vector2f(0, 100));
    shape->setPosition(300, 300);
    shape->setFillColor(sf::Color::Red);
    
    setPosition(300, 300);
    
    isStatic = false;
    
    PhysicsManager::AddShape(*this, *shape);
}

//NOTE PHYSICS IS ALL FUCKED UP
TestPhysicsObject::TestPhysicsObject(sf::Vector2f position, bool isStatic):PhysicsObject(){
    shape = new sf::ConvexShape();
    shape->setPointCount(3);
    shape->setPoint(2, sf::Vector2f(0,0));
    shape->setPoint(1, sf::Vector2f(100,0));
    shape->setPoint(0, sf::Vector2f(0, 100));
    shape->setPosition(position);
    shape->setFillColor(sf::Color::Red);
    
    setPosition(position);

    this->isStatic = isStatic;
    
    PhysicsManager::AddShape(*this, *shape);
}

void TestPhysicsObject::Update(){
    //shape->rotate(6);
}

void TestPhysicsObject::Draw(sf::RenderWindow& window){
    window.draw(*shape);
}

//THIS FUNCTION IS TEMPORARY.
//THE ONLY REASON IT IS HERE IS BECAUSE SHAPES ARE NOT YET DRAWN RELATIVE TO THEIR BODIES
void TestPhysicsObject::UpdateTransform(b2Body* box2DBody){
    b2Vec2 origin = box2DBody->GetLocalCenter(); //Should we be updating origin?
    b2Vec2 position = box2DBody->GetPosition();
    float angle = box2DBody->GetAngle();
    shape->setOrigin(origin.x, origin.y);
    shape->setPosition(position.x, position.y);
    shape->setRotation(angle);
}


