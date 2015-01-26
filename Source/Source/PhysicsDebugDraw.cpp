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
	sf::Vertex* sfVerts = (sf::Vertex*)alloca(sizeof(b2Vec2) * vertexCount);
    for(int32 i=0; i<vertexCount; ++i){
        sfVerts[i].position.x = vertices[i].x;
        sfVerts[i].position.y = vertices[i].y;
        fprintf(stderr, "Number!: %d, %f\n", i, sfVerts[i].position.x);
        sfVerts[i].color = sf::Color::Blue;
    }
    target->draw(sfVerts, vertexCount, sf::Triangles);
}