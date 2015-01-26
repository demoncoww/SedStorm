//
//  TestPhysicsObject.h
//  Sedimental Storm
//
//  Created by Jacob Cohen on 1/22/15.
//  Copyright (c) 2015 Jacob Cohen. All rights reserved.
//

#ifndef __Sedimental_Storm__TestPhysicsObject__
#define __Sedimental_Storm__TestPhysicsObject__

#include <stdio.h>
#include "PhysicsObject.h"
#include "PhysicsManager.h"


class TestPhysicsObject: public virtual PhysicsObject, public virtual sf::ConvexShape
{
public:
    TestPhysicsObject();
    TestPhysicsObject(sf::Vector2f position, bool isStatic);
    virtual void Update();
    virtual void Draw(sf::RenderTarget& window, sf::RenderStates& renderState);
};

#endif /* defined(__Sedimental_Storm__TestPhysicsObject__) */
