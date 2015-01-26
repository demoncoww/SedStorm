//
//  PhysicsBody.cpp
//  Sedimental Storm
//
//  Created by Jacob Cohen on 1/13/15.
//  Copyright (c) 2015 Jacob Cohen. All rights reserved.
//

#include "PhysicsBody.h"

void PhysicsBody::UpdateParentTransform(){
    parent->UpdateTransform(body);
}