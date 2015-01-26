//
//  Sliceable.h
//  Sedimental Storm
//
//  Created by Jacob Cohen on 1/26/15.
//  Copyright (c) 2015 Jacob Cohen. All rights reserved.
//

#ifndef __Sedimental_Storm__Sliceable__
#define __Sedimental_Storm__Sliceable__

#include <stdio.h>
#include "PhysicsObject.h"
#include "PhysicsManager.h"

class Sliceable: public virtual PhysicsObject
{
public:
    Sliceable(sf::Vector2f position, std::vector<sf::Vector2f>& points, bool isThisStatic);
};

#endif /* defined(__Sedimental_Storm__Sliceable__) */
