//
//  PhysicsObject.h
//  Sedimental Storm
//
//  Created by Jacob Cohen on 1/22/15.
//  Copyright (c) 2015 Jacob Cohen. All rights reserved.
//

#ifndef __Sedimental_Storm__PhysicsObject__
#define __Sedimental_Storm__PhysicsObject__

#include <stdio.h>
#include <Box2D/Box2D.h>
#include "GameObject.h"

class PhysicsBody; //Forward declaring PhysicsBody as they both require references to each other

class PhysicsObject: public virtual GameObject, public virtual sf::ConvexShape {
public:
    PhysicsBody* body;
    bool isStatic = false;
    virtual void SetParent(GameObject* parent);
    void UpdateTransform(b2Body* box2DBody);
    virtual void Draw(sf::RenderTarget& target, sf::RenderStates& renderState);
protected:
    PhysicsObject();
    PhysicsObject (const PhysicsObject& obj);
};

#endif /* defined(__Sedimental_Storm__PhysicsObject__) */
