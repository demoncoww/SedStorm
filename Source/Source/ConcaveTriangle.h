//
//  Triangle.h
//  Sedimental Storm
//
//  Created by Jacob Cohen on 1/20/15.
//  Copyright (c) 2015 Jacob Cohen. All rights reserved.
//

#ifndef __Sedimental_Storm__ConcaveTriangle__
#define __Sedimental_Storm__ConcaveTriangle__

#include <stdio.h>
#include "GameObject.h"
#include <Thor/Math.hpp>


class ConcaveTriangle : public virtual GameObject, public virtual thor::ConcaveShape
{
public:
    ConcaveTriangle();
    virtual void update();
	virtual void draw(sf::RenderTarget& window, sf::RenderStates& renderState);
};

#endif /* defined(__Sedimental_Storm__ConcaveTriangle__) */
