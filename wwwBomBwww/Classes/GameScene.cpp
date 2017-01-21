//
//  GameScene.cpp
//  wwwBomBwww
//
//  Created by 蔵元隼人 on 2017/01/21.
//
//

#include "GameScene.hpp"
#include "MultiResolution.h"

bool GameScene::init()
{
    if(!Scene::init())
    {
        return false;
    }
    
    _gameLayer = GameLayer::create();
    this->addChild(_gameLayer);
    
    this->scheduleUpdate();
    return true;
}

void GameScene::update(float delta)
{
    
}
