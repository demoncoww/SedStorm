//
//  Sliceable.cpp
//  Sedimental Storm
//
//  Created by Jacob Cohen on 1/26/15.
//  Copyright (c) 2015 Jacob Cohen. All rights reserved.
//

#include "Sliceable.h"

Sliceable::Sliceable(sf::Vector2f position, std::vector<sf::Vector2f>& points, bool isThisStatic){
    setPosition(position);
    setPointCount(points.size());
    for(unsigned int i=0; i<points.size(); ++i){
        setPoint(i, points[i]);
    }
    
    setFillColor(sf::Color::Green);
    
    isStatic = isThisStatic;
    
    //This should be changed to AddConcaveShape once that functionality is added
    PhysicsManager::AddShape(*this);
};
