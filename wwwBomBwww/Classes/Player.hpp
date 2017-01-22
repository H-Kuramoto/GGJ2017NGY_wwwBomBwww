//
//  Player.hpp
//  wwwBomBwww
//
//  Created by 蔵元隼人 on 2017/01/22.
//
//

#ifndef Player_hpp
#define Player_hpp

#define player_Charge_animName "ChargeAnim"
#define player_win_AnimName "winAnim"

#include <stdio.h>
#include "cocos2d.h"
#include "Effect.h"

USING_NS_CC;

class Player : public Sprite
{
public:
    static Player *create(bool isLeftChara);
    bool init(bool isLeftChara);
    
    void powerCharge();
    void appearWave();
    void result(bool isWin);
    void reset();
private:
    bool _isCharging;
    bool _isLeftChara;
    Effect *_effect;
    
    int _soundID;
    int _chargeSound;
    
    };


#endif /* Player_hpp */
