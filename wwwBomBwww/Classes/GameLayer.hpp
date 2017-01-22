//
//  GameLayer.hpp
//  wwwBomBwww
//
//  Created by 蔵元隼人 on 2017/01/21.
//
//

#ifndef GameLayer_hpp
#define GameLayer_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "WaveManager.hpp"
#include "Bomb.hpp"
#include "Player.hpp"

USING_NS_CC;

class GameLayer : public Layer
{
public:
    CREATE_FUNC(GameLayer);
    bool init();
    void update(float delta);
    
    Node *_waveRegioin;
    WaveManager *_waveManager;
    Bomb        *_bomb;
    Player      *_playerSp[2];
    
    
    void gameFinish();
private:
    
    
};

#endif /* GameLayer_hpp */
