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


class GameObject: public virtual sf::Transformable
{
friend class GameObjectManager;
public:
    GameObject& operator=(const GameObject& obj);
    virtual void Update();
	virtual void Draw(sf::RenderTarget& target, sf::RenderStates& renderState);
    virtual ~GameObject();
    void SetParent(GameObject* parent);
    inline GameObject& GetParent(){return *_parent;}
    inline std::vector<GameObject*>& GetChildren(){return _children;}
	bool IsTopLevel(); // returns true if the GameObject has no parent, as we only want to draw these, not children
protected:
    //Constructors are protected to force use of factory functions
    GameObject();
    GameObject (const GameObject& obj);
    GameObject* _parent;
    std::vector<GameObject*> _children;
};

#endif /* defined(__Sedimental_Storm__GameObject__) */
