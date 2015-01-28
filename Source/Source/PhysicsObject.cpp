//
//  PhysicsObject.cpp
//  Sedimental Storm
//
//  Created by Jacob Cohen on 1/22/15.
//  Copyright (c) 2015 Jacob Cohen. All rights reserved.
//

#include "PhysicsObject.h"

//override set parent so that physicsObjects never have a parent.
void PhysicsObject::SetParent(GameObject* parent){
    fprintf(stderr, "Cannot set parent of physics object");
}

PhysicsObject::PhysicsObject():GameObject()
{
}

PhysicsObject::PhysicsObject(const PhysicsObject& obj):GameObject(obj)
{
}

//Updates the transform to match that of the b2body
void PhysicsObject::UpdateTransform(b2Body* box2DBody){
    b2Vec2 origin = box2DBody->GetLocalCenter(); //Should we be updating origin?
    b2Vec2 position = box2DBody->GetPosition();
	float angle = thor::toDegree(box2DBody->GetAngle());
    
    setOrigin(origin.x, origin.y);
    setPosition(position.x, position.y);
    setRotation(angle);
}

void PhysicsObject::Draw(sf::RenderTarget& target, sf::RenderStates& renderState){
    target.draw(*this);
}




