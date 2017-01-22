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
#include "Effect.h"

USING_NS_CC;

class GameScene : public Scene
{
public:
    CREATE_FUNC(GameScene);
    bool init();
    void update(float delta);
    
    GameLayer *_gameLayer;
    Sprite *_timerSp;
    Effect *_startEffect;
    
    void gameStart();
    void gameFinish();
    
    // タッチ
    void onTouchesBegan(const std::vector<Touch *> &touches, cocos2d::Event *unused_event); // タッチ開始
    void onTouchesEnded(const std::vector<Touch *> &touches, cocos2d::Event *unused_event); // タッチ終了
    void onTouchesMoved(const std::vector<Touch *> &touches, cocos2d::Event *unused_event); // スワイプ
    // キー入力
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);private:
private:
    int _time;
    int _frameCnt;
    bool _isPlay;
    bool _isWaiteRetry;
    
    
    
};


#endif /* GameScene_hpp */
