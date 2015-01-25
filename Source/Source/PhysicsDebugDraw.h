//
//  PhysicsDebugDraw.h
//  Sedimental Storm
//
//  Created by Jacob Cohen on 1/23/15.
//  Copyright (c) 2015 Jacob Cohen. All rights reserved.
//

#ifndef __Sedimental_Storm__PhysicsDebugDraw__
#define __Sedimental_Storm__PhysicsDebugDraw__

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class PhysicsDebugDraw : public b2Draw
{
public:
    PhysicsDebugDraw(sf::RenderTarget* theTarget);
    void SetTarget(sf::RenderTarget* theTarget);
    virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {}
    virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
    virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {}
    virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) {}
    virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {}
    virtual void DrawTransform(const b2Transform& xf) {}
private:
    sf::RenderTarget* target;
};

#endif /* defined(__Sedimental_Storm__PhysicsDebugDraw__) */
