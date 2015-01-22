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
#include <GameLayer.h>

class GameObjectManager{
public:
    static sf::RenderWindow window;
    GameObjectManager();
    void drawLayers();
    void updateLayers();
    bool pauseLayer(std::string& layerName);
    bool resumeLayer(std::string& layerName);
    void addLayer(std::string& layerName, Layer& layer);
    GameLayer* createGameLayer(std::string& layerName, bool isActive, bool isVisible);
    bool removeLayer(std::string& layerName);
private:
    std::vector<Layer*> _world;
    std::map<std::string, Layer*> _layerNames;
};*/

#endif /* defined(__Sedimental_Storm__GameObjectManager__)
