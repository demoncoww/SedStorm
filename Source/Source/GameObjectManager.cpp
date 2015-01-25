//
//  GameObjectManager.cpp
//  Sedimental Storm
//
//  Created by Jacob Cohen on 1/14/15.
//  Copyright (c) 2015 Jacob Cohen. All rights reserved.
//

#include "GameObjectManager.h"

GameObjectManager::GameObjectManager(): _world(0), _layerNames()
{}

GameLayer* GameObjectManager::CreateGameLayer(std::string& layerName, bool isActive, bool isVisible){
    GameLayer* newLayer = new GameLayer(isActive, isVisible);
    AddLayer(layerName, *newLayer);
    return newLayer;
}

// Draws all of the visible layers in _world
void GameObjectManager::DrawLayers(sf::RenderWindow& window){
    for(unsigned int i=0; i<_world.size();++i){
        if(_world[i]->isVisible()){
            _world[i]->drawObjects(window);
        }
    }
}

// Updates all the active layers in _world
void GameObjectManager::UpdateLayers(){
    for(unsigned int i=0; i<_world.size();++i){
        if(_world[i]->isActive()){
            _world[i]->updateObjects();
        }
    }
}

/* Pauses a particular layer, preventing it from calling its update function
 *
 * @param layerName		The name of the layer to be paused
 * @returns             True if the layer was found and paused, false otherwise
 *
 */
bool GameObjectManager::PauseLayer(std::string& layerName)
{
    auto layerIterator = _layerNames.find(layerName);
    if(layerIterator != _layerNames.end()){ //Layer exists
        layerIterator->second->pause();
        return true;
    }
    return false;
}

/* Resumes a particular layer, allowing it to call its update function
 *
 * @param layerName		The name of the layer to be resumed
 * @returns             True if the layer was found and resumed, false otherwise
 *
 */
bool GameObjectManager::ResumeLayer(std::string& layerName)
{
    auto layerIterator = _layerNames.find(layerName);
    if(layerIterator != _layerNames.end()){ //Layer exists
        layerIterator->second->resume();
        return true;
    }
    return false;
}

/* Adds a layer to the GameObjectManager's layer list. Uses the passed string as the key.
 *
 * @param layerName	 	The key to be associated with the Layer
 * @param layer		    The layer to be added to the list
 * @returns             void
 *
 */
void GameObjectManager::AddLayer(std::string& layerName, Layer& layer)
{
    _layerNames[layerName] = &layer;
    _world.push_back(&layer);
}

/* removes a layer from the GameObjectManager's layer list. Uses the passed string as the key.
 *
 * @param layerName	 	The key of the layer to be removed
 * @returns             true if the layer was found and removed
 *
 */
//Should this delete the removed layer?
bool GameObjectManager::RemoveLayer(std::string& layerName)
{
    auto layerIterator = _layerNames.find(layerName);
    if(layerIterator != _layerNames.end()){ //Layer exists
        auto position = std::find(_world.begin(), _world.end(), layerIterator->second); //find layer in layers
        if(position == _world.end()){
            fprintf(stderr, "layer %s was found in layerName but not _world", layerName.c_str());
            return false;
        }
        _layerNames.erase(layerName);
        _world.erase(position);
        return true;
    }
    return false;
}
