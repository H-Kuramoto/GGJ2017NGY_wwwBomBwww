//
//  WaveTile.cpp
//  wwwBomBwww
//
//  Created by 蔵元隼人 on 2017/01/21.
//
//

#include "WaveTile.hpp"

bool WaveTile::init()
{
    if(!Sprite::init())
    {
        return false;
    }
    
    _dir = MOVE_DIR::STOP;
    _speed = 0.0f;
    _power = 0.0f;
    
    
    // spriteとして初期化
    this->initWithFile("GameScene/wave/wave.png");
    
    return true;
}

void WaveTile::update(float delta)
{
    
    
    
    
    
}

void WaveTile::moveWave()
{
    // スケーリングの変更
    float n = _power/POWER_MAX;
    float scaleY = (1 - n) * SCALE_MIN + n * SCALE_MAX;
    this->setScaleY(scaleY);
    
}

void WaveTile::affectedByWaves(WaveTile::MOVE_DIR dir, float speed, float power)
{
    // 波の力を受ける
    _power = power;
    
    // 移動方向決定
    if(_dir != dir)
    {
    }
    
}
