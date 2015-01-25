
//
//  Triangle.cpp
//  Sedimental Storm
//
//  Created by Jacob Cohen on 1/20/15.
//  Copyright (c) 2015 Jacob Cohen. All rights reserved.
//

#include "Triangle.h"

Triangle::Triangle(){
    shape = new sf::ConvexShape();
    shape->setPointCount(3);
    shape->setPoint(2, sf::Vector2f(0,0));
    shape->setPoint(1, sf::Vector2f(100,0));
    shape->setPoint(0, sf::Vector2f(0, 100));
    shape->setFillColor(sf::Color::Green);
}

void Triangle::Update(){
    shape->rotate(3);
}

//sf::Vector2f deltaTransformPoint(sf::Transform matrix, sf::Vector2f point) {
//    float dx = point.x * matrix.getMatrix()[0] + point.y * matrix.getMatrix()[1] + 0;
//    float dy = point.x * matrix.getMatrix()[3] + point.y * matrix.getMatrix()[4] + 0;
//    return sf::Vector2f(dx, dy);
//}
//
//void decomposeMatrix(sf::Transform matrix, sf::Transformable& shape) {
//
//    // @see https://gist.github.com/2052247
//
//    // calculate delta transform point
//    sf::Vector2f px = deltaTransformPoint(matrix, sf::Vector2f(0, 1));
//    sf::Vector2f py = deltaTransformPoint(matrix, sf::Vector2f(1, 0));
//
//    // calculate skew
//    float skewX = ((180 / thor::Pi) * atan2(px.y, px.x) - 90);
//    float skewY = ((180 / thor::Pi) * atan2(py.y, py.x));
//
//    float scaleX = sqrt(matrix.getMatrix()[0] * matrix.getMatrix()[0] + matrix.getMatrix()[3] * matrix.getMatrix()[3]);
//    float scaleY = sqrt(matrix.getMatrix()[1] * matrix.getMatrix()[1] + matrix.getMatrix()[4] * matrix.getMatrix()[4]);
//    shape.setScale(scaleX, scaleY);
//    shape.setOrigin(0, 0);
//    shape.setRotation(skewX);
//}

void Triangle::Draw(sf::RenderTarget& window, sf::RenderStates& renderState) {
    // we can't copy renderstates transform into shapes transform :(
    // decomposeMatrix(renderState.transform, *shape);
    window.draw(*shape, renderState);
}

