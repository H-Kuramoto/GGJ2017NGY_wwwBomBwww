//
//  Player.cpp
//  wwwBomBwww
//
//  Created by 蔵元隼人 on 2017/01/22.
//
//

#include "Player.hpp"
#include "AnimationManager.h"

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
    
    this->initWithFile("GameScene/player/main/player_01.png");
    this->setFlippedX(!isLeftChara);
    
    _effect = Effect::Create(this, EffectID::ChargeEffect);
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
    }
}

void Player::appearWave()
{
    if(_isCharging)
    {
        this->stopAllActions();
        _isCharging = false;
        _effect->End();
    }
}

void Player::result(bool isWin)
{
    if(isWin)
    {
        this->stopAllActions();
        AnimationManager::runParaparaAnimation(this, player_win_AnimName);
    }
    else
    {
        this->setTexture("GameScene/player/result/player_left_lose_01.png");
    }
}

void Player::reset()
{
    this->stopAllActions();
    this->setTexture("GameScene/player/main/player_01.png");
}





















