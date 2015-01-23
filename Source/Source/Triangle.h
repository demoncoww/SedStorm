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


class Triangle: public GameObject
{
public:
    Triangle();
    sf::ConvexShape* shape;
    virtual void update();
	virtual void draw(sf::RenderTarget& window, sf::RenderStates& renderState);
};

#endif /* defined(__Sedimental_Storm__Triangle__) */
