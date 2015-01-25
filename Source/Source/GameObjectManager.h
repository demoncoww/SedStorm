//
//  GameObjectManager.h
//  Sedimental Storm
//
//  Created by Jacob Cohen on 1/14/15.
//  Copyright (c) 2015 Jacob Cohen. All rights reserved.
//

#ifndef __Sedimental_Storm__GameObjectManager__
#define __Sedimental_Storm__GameObjectManager__

#include <stdio.h>
#include <vector>
#include <string>
#include <map>
#include "GameLayer.h"

class GameObjectManager{
public:
    GameObjectManager();
    void DrawLayers(sf::RenderWindow& window);
    void UpdateLayers();
    bool PauseLayer(std::string& layerName);
    bool ResumeLayer(std::string& layerName);
    void AddLayer(std::string& layerName, Layer& layer);
    GameLayer* CreateGameLayer(std::string& layerName, bool isActive, bool isVisible);
    bool RemoveLayer(std::string& layerName);
private:
    std::vector<Layer*> _world;
    std::map<std::string, Layer*> _layerNames;
};

#endif /* defined(__Sedimental_Storm__GameObjectManager__) */
