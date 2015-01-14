//
//  GameObject.h
//  Sedimental Storm
//
//  Created by Jacob Cohen on 1/13/15.
//  Copyright (c) 2015 Jacob Cohen. All rights reserved.
//

#ifndef __Sedimental_Storm__GameObject__
#include <Box2D/Box2D.h>
#define __Sedimental_Storm__GameObject__

#include <stdio.h>
#include <vector>

#endif /* defined(__Sedimental_Storm__GameObject__) */

class GameObject{
friend class GameObjectManager;
public:
    GameObject& operator=(const GameObject& obj);
    virtual void draw();
    virtual void update();
    virtual ~GameObject();
    void setParent(GameObject& parent);
    inline b2Vec2 getPosition(){return _position;}
    inline float getAngle(){return _angle;}
    inline b2Vec2 getScale(){return _scale;}
    inline GameObject& getParent(){return *_parent;}
    inline std::vector<GameObject*>& getChildren(){return _children;}
protected:
    //Constructors are protected to force use of factory functions
    GameObject();
    GameObject (const GameObject& obj);
    b2Vec2 _position;
    float _angle; //in radians
    b2Vec2 _scale;
    GameObject* _parent;
    std::vector<GameObject*> _children;
};
