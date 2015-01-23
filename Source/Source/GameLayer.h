//
//  GameLayer.h
//  Sedimental Storm
//
//  Created by Jacob Cohen on 1/20/15.
//  Copyright (c) 2015 Jacob Cohen. All rights reserved.
//

#ifndef __Sedimental_Storm__GameLayer__
#define __Sedimental_Storm__GameLayer__

#include <stdio.h>
#include "Layer.h"

class GameLayer: public Layer{
public:
    GameLayer();
    GameLayer(bool isVisible, bool isActive);
};

#endif /* defined(__Sedimental_Storm__GameLayer__) */
