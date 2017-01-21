//
//  WaveTile.hpp
//  wwwBomBwww
//
//  Created by 蔵元隼人 on 2017/01/21.
//
//

#ifndef WaveTile_hpp
#define WaveTile_hpp

#include <stdio.h>
#include "cocos2d.h"

#define SCALE_MAX 1.0f
#define SCALE_MIN 0.5f
#define SPEED_MAX 10.0f
#define POWER_MAX 10.0f

USING_NS_CC;

class WaveTile : public Sprite
{
public:
    // 移動方向
    enum MOVE_DIR
    {
        LEFT = -1,
        STOP = 0,
        RGHITE = 1
    };
    struct WaveStatus
    {
        MOVE_DIR dir;
        float power;   // 波の力
    };
    
    CREATE_FUNC(WaveTile);
    bool init();
    void update(float delta);

    void affectedByWaves(WaveStatus otherStatus);
    
    
    WaveStatus _status;
    
        
    
private:
    
    
};

#endif /* WaveTile_hpp */
