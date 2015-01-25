//
//  PhysicsDebugDraw.cpp
//  Sedimental Storm
//
//  Created by Jacob Cohen on 1/23/15.
//  Copyright (c) 2015 Jacob Cohen. All rights reserved.
//

#include "PhysicsDebugDraw.h"

PhysicsDebugDraw::PhysicsDebugDraw(sf::RenderTarget* theTarget){
    SetTarget(theTarget);
    SetFlags( b2Draw::e_shapeBit );
}

void PhysicsDebugDraw::SetTarget(sf::RenderTarget* theTarget){
    target = theTarget;
}

void PhysicsDebugDraw::DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color){
    sf::Vertex* sfVerts = new sf::Vertex[vertexCount];
    for(int32 i=0; i<vertexCount; ++i){
        sfVerts[i].position = sf::Vector2f(vertices[i].x, vertices[i].y);
        sfVerts[i].color = sf::Color::Blue;
    }
    target->draw(sfVerts, vertexCount, sf::Triangles);
}