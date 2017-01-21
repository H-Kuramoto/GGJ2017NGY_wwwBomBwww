//
//  GameScene.hpp
//  wwwBomBwww
//
//  Created by 蔵元隼人 on 2017/01/21.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "GameLayer.hpp"

USING_NS_CC;

class GameScene : public Scene
{
public:
    CREATE_FUNC(GameScene);
    bool init();
    void update(float delta);
    
    GameLayer *_gameLayer;
    
private:

    
    
    
};


#endif /* GameScene_hpp */
