//
//  GameLayer.cpp
//  wwwBomBwww
//
//  Created by 蔵元隼人 on 2017/01/21.
//
//

#include "GameLayer.hpp"
#include "MultiResolution.h"

#include <SimpleAudioEngine.h>
#include "AnimationManager.h"

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
    _bomb->setPositionY(300);
    _waveRegioin->addChild(_bomb);
    
    
    AnimationManager::addAnimationCachePluralFile("GameScene/player/main/player_0%d.png", player_Charge_animName, 1, 3, false, 0.2f);
    AnimationManager::addAnimationCachePluralFile("GameScene/player/result/player_left_win_0%d.png", player_win_AnimName, 1, 2, false, 0.2);
    
    float height = 550.0f;
    
    _playerSp[0] = new Player();
    this->addChild(_playerSp[0]);
    _playerSp[0]->init(true);
    _playerSp[0]->setPosition(Vec2(200,height));
    
    _playerSp[1] = new Player();
    this->addChild(_playerSp[1]);
    _playerSp[1]->init(false);
    _playerSp[1]->setPosition(Vec2(designResolutionSize.width - 200,height));
    
    
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

void GameLayer::gameFinish()
{
    // 爆弾が開始地点からどちらに近いか
    float dis = _bomb->getPositionX() - WAVE_REGION_WIDTH/2;
    
    bool winLeft;
    
    if(dis < 0) // 左の負け
    {
        winLeft = false;
        log ("WIN_RIGHT");
    }
    else if(dis > 0) // 右の負け
    {
        winLeft = true;
        log("WIN_LEFT");
    }
    else // 引き分け
    {
        for(int i = 0; i < 2; i++)
        {
            _playerSp[i]->result(false);
        }
        log("DOROW");
        return;
    }
    
    _waveManager->unscheduleUpdate();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/explode.wav");
    
    AnimationManager::runParaparaAnimation(_bomb, bomb_AnimName, false);
    _bomb->destroySet();
    
    _playerSp[0]->result(winLeft);
    _playerSp[1]->result(!winLeft);
}





















