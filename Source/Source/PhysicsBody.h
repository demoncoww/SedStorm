//
//  PhysicsBody.h
//  Sedimental Storm
//
//  Created by Jacob Cohen on 1/13/15.
//  Copyright (c) 2015 Jacob Cohen. All rights reserved.
//

#ifndef __Sedimental_Storm__PhysicsBody__
#define __Sedimental_Storm__PhysicsBody__

#include <stdio.h>
#include <Box2D/Box2D.h>
#include "PhysicsObject.h"

class PhysicsObject;

class PhysicsBody
{
public:
    void UpdateParentTransform();
    b2Body* body;
    PhysicsObject* parent;
};

#endif /* defined(__Sedimental_Storm__PhysicsBody__) */
