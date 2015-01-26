//
//  Triangle.h
//  Sedimental Storm
//
//  Created by Jacob Cohen on 1/20/15.
//  Copyright (c) 2015 Jacob Cohen. All rights reserved.
//

#ifndef __Sedimental_Storm__Triangle__
#define __Sedimental_Storm__Triangle__

#include <stdio.h>
#include "GameObject.h"
#include <Thor/Math.hpp>


class Triangle: public GameObject
{
public:
    Triangle();
    sf::ConvexShape* shape; // we aren't using the transformable base class of shape
    virtual void Update();
	virtual void Draw(sf::RenderTarget& window, sf::RenderStates& renderState);
};

#endif /* defined(__Sedimental_Storm__Triangle__) */
