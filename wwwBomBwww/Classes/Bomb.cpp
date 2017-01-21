//
//  Bomb.cpp
//  wwwBomBwww
//
//  Created by 蔵元隼人 on 2017/01/21.
//
//

#include "Bomb.hpp"

bool Bomb::init()
{
    if(!Sprite::init())
    {
        return false;
    }
    
    this->initWithFile("GameScene/bomb/bomb_01.png");
    this->setScale(0.5f);
    this->scheduleUpdate();
    
    
    return true;
}

void Bomb::update(float delta)
{
    this->setPositionY(this->getPositionY() - BOMB_GRAVITY);
}

void Bomb::moveX(int dir, float wavePower)
{
    
    this->setPositionX(this->getPositionX() + (dir * wavePower/1.5f));
    this->setPositionY(this->getPositionY() + 0.6f + wavePower/1.0f - BOMB_GRAVITY);
    if(dir == 1)
    {
        this->setFlippedX(true);
    }
    else if(dir == -1)
    {
        this->setFlippedX(false);
    }
}

Rect Bomb::getRect()
{
    //少し小さめのコリジョンを作る
    Rect temp = this->getBoundingBox();
    Vec2 pos;
    pos.x = temp.getMinX();
    pos.y = temp.getMidY();
   
    Rect hitCollision;
    hitCollision = Rect(pos, temp.size/2);
    
    return hitCollision;

}
