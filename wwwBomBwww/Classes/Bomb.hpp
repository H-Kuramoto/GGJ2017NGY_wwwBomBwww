//
//  Bomb.hpp
//  wwwBomBwww
//
//  Created by 蔵元隼人 on 2017/01/21.
//
//

#ifndef Bomb_hpp
#define Bomb_hpp

#define BOMB_GRAVITY 0.5f
#define bomb_AnimName "bombAnim"

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class Bomb : public Sprite
{
public:
    CREATE_FUNC(Bomb);
    bool init();
    void update(float delta);
    
    void moveX(int dir, float wavePower);
    Rect getRect();
private:
};

#endif /* Bomb_hpp */
;
