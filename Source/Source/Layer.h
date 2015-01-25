//
//  Layer.h
//  Sedimental Storm
//
//  Created by Jacob Cohen on 1/20/15.
//  Copyright (c) 2015 Jacob Cohen. All rights reserved.
//

#ifndef __Sedimental_Storm__Layer__
#define __Sedimental_Storm__Layer__

#include <stdio.h>
#include <vector>
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderStates.hpp>
//#include <GameObjectManager.h>

class Layer{
public:
    std::vector<GameObject*> objects;
    ~Layer(); //delete all GameObjects in objects
    void UpdateObjects();
    void DrawObjects(sf::RenderWindow& window);
    inline void Pause(){ isActive = false; }
    inline void Resume(){ isActive = true; }
    inline void Disable(){ isVisible = false; isActive = false; };
    inline void Enable(){ isVisible = true; isActive = true; }
    inline bool IsActive(){ return isActive;}
    inline bool IsVisible(){ return isVisible;}
protected:
    Layer(); //constructor is protected so that this class will be treated as an interface
    Layer(bool isVisible, bool isActive);
    bool isVisible; //Should this layers draw function be called
    bool isActive; //Should this layers update function be called
	void DrawChildren(sf::RenderTarget& target, GameObject* parent, sf::RenderStates& renderState);
};

#endif /* defined(__Sedimental_Storm__Layer__) */
