//
//  WaveTile.cpp
//  wwwBomBwww
//
//  Created by 蔵元隼人 on 2017/01/21.
//
//

#include "WaveTile.hpp"
#include "AnimationManager.h"
bool WaveTile::init()
{
    if(!Sprite::init())
    {
        return false;
    }
    
    _status.dir = MOVE_DIR::STOP;
    _status.power = 0.0f;

    
    // spriteとして初期化
    this->initWithFile("GameScene/main_wave/main_wave_01.png");
    this->setAnchorPoint(Vec2(0.5f, 0.0f));
    this->setScaleY(SCALE_MIN);
    this->scheduleUpdate();
    
    // 波のアニメーション
    AnimationManager::addAnimationCachePluralFile("GameScene/main_wave/main_wave_0%d.png", "waveAnim", 1, 6, false, 0.5f);
    AnimationManager::runParaparaAnimation(this, "waveAnim");
    
    return true;
}

void WaveTile::update(float delta)
{
//
//    if(_dir != STOP)
//    {
//        moveWave();
//    }
  
}

void WaveTile::affectedByWaves(WaveStatus otherStatus)
{
    
    this->stopAllActions();
    
    // 移動方向決定
    if(_status.dir == STOP)
    {
        _status.power = otherStatus.power;
        _status.dir = otherStatus.dir;
    }
    else if(_status.power < otherStatus.power)
    {
        _status.power = otherStatus.power - _status.power;
        _status.dir = otherStatus.dir;
    }
    else if(_status.power == otherStatus.power)
    {
        _status.dir = STOP;
    }
    
    float n = _status.power/POWER_MAX;
    float scaleY = (1 - n) * SCALE_MIN + n * SCALE_MAX;
    
    Sequence *seq = Sequence::create(
                                     ScaleTo::create(0.5f, this->getScaleX(), scaleY),
                                     ScaleTo::create(0.5f, this->getScaleX(), SCALE_MIN),
                                     CallFunc::create([=](){_status.dir = STOP; _status.power = 0.0f;}),
                                     NULL
                                     );
    // 波打ちます
    this->runAction(seq);
    AnimationManager::runParaparaAnimation(this, "waveAnim");
}
