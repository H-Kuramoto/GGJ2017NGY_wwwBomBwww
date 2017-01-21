//
//  GameLayer.cpp
//  wwwBomBwww
//
//  Created by 蔵元隼人 on 2017/01/21.
//
//

#include "GameLayer.hpp"
#include "MultiResolution.h"
bool GameLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    Sprite *backGroundSp = Sprite::create("GameScene/backGround/main_field_back.png");
    backGroundSp->setPosition(designResolutionSize/2);
    this->addChild(backGroundSp);
    
    
    
    _waveRegioin = Node::create();
    this->addChild(_waveRegioin);
    _waveRegioin->setPositionX(310);
    
    _waveManager = WaveManager::create();
    _waveRegioin->addChild(_waveManager);
    
    _bomb = Bomb::create();
    _bomb->setPositionX(WAVE_REGION_WIDTH/2);
    _bomb->setPositionY(500);
    _waveRegioin->addChild(_bomb);
    
    
    
    Sprite *gakeSp = Sprite::create("GameScene/backGround/main_field.png");
    gakeSp->setPosition(
                        gakeSp->getBoundingBox().size.width/2,
                        gakeSp->getBoundingBox().size.height/2
                        );
    this->addChild(gakeSp);

    
    this->scheduleUpdate();
    
    return true;
}

void GameLayer::update(float delta)
{
    
}
