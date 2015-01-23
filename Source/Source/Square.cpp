//
//  Square.cpp
//  Sedimental Storm
//
//  Created by Jacob Cohen on 1/20/15.
//  Copyright (c) 2015 Jacob Cohen. All rights reserved.
//

#include "Square.h"

Square::Square(): verts(sf::Triangles, 3)
{
    
    // create an array of 3 vertices that define a triangle primitive
    // define the position of the triangle's points
    verts[0].position = sf::Vector2f(10, 10);
    verts[1].position = sf::Vector2f(100, 10);
    verts[2].position = sf::Vector2f(100, 100);
    
    // define the color of the triangle's points
    verts[0].color = sf::Color::Red;
    verts[1].color = sf::Color::Blue;
    verts[2].color = sf::Color::Green;
}

void Square::update(){
    move(3,0);
}

void Square::draw(sf::RenderTarget& target, sf::RenderStates states){
    // apply the entity's transform -- combine it with the one that was passed by the caller
    states.transform *= getTransform(); // getTransform() is defined by sf::Transformable
    
    // apply the texture
    states.texture = nullptr;
    
    // you may also override states.shader or states.blendMode if you want
    
    // draw the vertex array
    target.draw(verts, states);
}