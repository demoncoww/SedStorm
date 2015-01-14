//
//  GameObject.cpp
//  Sedimental Storm
//
//  Created by Jacob Cohen on 1/13/15.
//  Copyright (c) 2015 Jacob Cohen. All rights reserved.
//

#include "GameObject.h"

GameObject::GameObject() : _position(0,0), _angle(0), _scale(1,1), _parent(nullptr)
{
}

//Copy constructor does not copy parent child relationships
GameObject::GameObject (const GameObject& obj) :
_position(obj._position),
_angle(obj._angle),
_scale(obj._scale),
_parent(nullptr)
{}


//If you assign one game object to another it will copy over parameters but not parent child relationships
GameObject& GameObject::operator=(const GameObject& obj){
    if(&obj == this){
        return *this;
    }
    
    _position = obj._position;
    _angle = obj._angle;
    _scale = obj._scale;
}

void GameObject::setParent(GameObject& parent){
    _parent = &parent;
    parent._children.push_back(this);
}

//Virtual functions
void GameObject::draw(){}
void GameObject::update(){}
GameObject::~GameObject(){}

