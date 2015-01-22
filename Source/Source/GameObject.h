//
//  GameObject.h
//  Sedimental Storm
//
//  Created by Jacob Cohen on 1/13/15.
//  Copyright (c) 2015 Jacob Cohen. All rights reserved.
//

#ifndef __Sedimental_Storm__GameObject__
#define __Sedimental_Storm__GameObject__

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <Thor/Shapes.hpp>
#include <vector>


class GameObject: sf::Transformable{
friend class GameObjectManager;
public:
    GameObject& operator=(const GameObject& obj);
    virtual void update();
    virtual void draw(sf::RenderWindow& window);
    virtual ~GameObject();
    void setParent(GameObject& parent);
    inline GameObject& getParent(){return *_parent;}
    inline std::vector<GameObject*>& getChildren(){return _children;}
protected:
    //Constructors are protected to force use of factory functions
    GameObject();
    GameObject (const GameObject& obj);
    GameObject* _parent;
    std::vector<GameObject*> _children;
};

#endif /* defined(__Sedimental_Storm__GameObject__) */
