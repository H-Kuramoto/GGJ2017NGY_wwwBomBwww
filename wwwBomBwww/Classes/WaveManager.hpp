//
//  WaveManager.hpp
//  wwwBomBwww
//
//  Created by 蔵元隼人 on 2017/01/21.
//
//

#ifndef WaveManager_hpp
#define WaveManager_hpp

#define WAVE_TILE_MAX 100
#define WAVE_REGION_WIDTH 1300.0f
#define WAVE_AFFECT_TIMING_MAX 7
#define WAVE_AFFECT_TIMING_MIN 2

#include <stdio.h>
#include "cocos2d.h"
#include "WaveTile.hpp"

USING_NS_CC;

class WaveManager : public Node
{
public:
    CREATE_FUNC(WaveManager);
    bool init();
    void update(float delta);
    
    void startWave(int elem, WaveTile::MOVE_DIR dir, float power);
    
    WaveTile *_waves[WAVE_TILE_MAX];
    int _affectTimer[WAVE_TILE_MAX];
    bool _isAffect[WAVE_TILE_MAX];
    float _waveAffectTiming[WAVE_TILE_MAX];
    
    float _power[2];
    bool _isTouching[2];
    int _toutchID[2];
    
    // タッチ
    void onTouchesBegan(const std::vector<Touch *> &touches, cocos2d::Event *unused_event); // タッチ開始
    void onTouchesEnded(const std::vector<Touch *> &touches, cocos2d::Event *unused_event); // タッチ終了
    void onTouchesMoved(const std::vector<Touch *> &touches, cocos2d::Event *unused_event); // スワイプ
    // キー入力
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);private:
    
    
private:
    int makeAffectTiming(float wavePower);
    int frameCnt;
    
};


#endif /* WaveManager_hpp */
