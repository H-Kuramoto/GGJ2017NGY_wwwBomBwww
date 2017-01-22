//
//  Player.cpp
//  wwwBomBwww
//
//  Created by 蔵元隼人 on 2017/01/22.
//
//

#include "Player.hpp"
#include "AnimationManager.h"

#include <SimpleAudioEngine.h>

Player* Player::create(bool isLeftChara)
{
    Player *pRet = new Player();
    
    if(pRet && pRet->init(isLeftChara))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool Player::init(bool isLeftChara)
{
    if(!Sprite::init())
    {
        return false;
    }
    
    _isLeftChara = isLeftChara;
    _isCharging = false;
    
    _soundID = 0;
    _chargeSound = 0;
    
    
    this->initWithFile("GameScene/player/main/player_01.png");
    this->setFlippedX(!isLeftChara);
    
    _effect = Effect::Create(this,Vec2(this->getBoundingBox().size.width/2,
                                       this->getBoundingBox().size.height/2),
                             EffectID::ChargeEffect
                             );
    
    _effect->SetPosition(Vec2(
                                this->getBoundingBox().size.width/2,
                                this->getBoundingBox().size.height/2
                                )
                         );
    
    return true;
}

void Player::powerCharge()
{
    if(!_isCharging)
    {
        this->stopAllActions();
        AnimationManager::runParaparaAnimation(this, player_Charge_animName);
        _isCharging = true;
        _effect->Start();
        
        _soundID = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/player_action.wav",true);
        _chargeSound = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/charge.wav",true);
    }
}

void Player::appearWave()
{
    if(_isCharging)
    {
        this->stopAllActions();
        _isCharging = false;
        _effect->End();
        CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(_soundID);
        CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(_chargeSound);
        
    }
}

void Player::result(bool isWin)
{
    
    Sprite *resultSp = Sprite::create();
    this->addChild(resultSp);
    resultSp->setPosition(Vec2(
                               this->getBoundingBox().size.width/2,
                               this->getBoundingBox().size.height/2
                               )
                          );
    
    if(isWin)
    {
        resultSp->setTexture("GameScene/result/win.png");
        this->stopAllActions();
        AnimationManager::runParaparaAnimation(this, player_win_AnimName);
    }
    else
    {
        resultSp->setTexture("GameScene/result/lose.png");
        this->setTexture("GameScene/player/result/player_left_lose_01.png");
    }
    
    resultSp->setScale(0.0f);
    
    float offset = 100;
    if(!_isLeftChara) offset = -offset;
    
    float logoAppTime = 1.5f;
    
    resultSp->runAction(Sequence::create(Spawn::create(EaseBounceOut::create(MoveBy::create(logoAppTime,Vec2(offset, 400))),
                                                       ScaleTo::create(logoAppTime, 1.0f),
                                                       NULL),
                                         NULL
                                         )
                        );
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/result.wav");
    
}

void Player::reset()
{
    this->stopAllActions();
    this->setTexture("GameScene/player/main/player_01.png");
}





















