//
//  Square.h
//  Sedimental Storm
//
//  Created by Jacob Cohen on 1/20/15.
//  Copyright (c) 2015 Jacob Cohen. All rights reserved.
//

#ifndef __Sedimental_Storm__Square__
#define __Sedimental_Storm__Square__

#include <stdio.h>
#include <GameObject.h>

#endif /* defined(__Sedimental_Storm__Square__) */

class Square: public GameObject{
public:
    Square();
    virtual void update();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states);
private:
    sf::VertexArray verts;
};