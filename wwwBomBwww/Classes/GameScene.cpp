//
//  GameScene.cpp
//  wwwBomBwww
//
//  Created by 蔵元隼人 on 2017/01/21.
//
//

#include "GameScene.hpp"
#include "MultiResolution.h"

#include <SimpleAudioEngine.h>

bool GameScene::init()
{
    if(!Scene::init())
    {
        return false;
    }
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/game_main_bgm.wav");
    
    _time = 10;
    _frameCnt = 0;
    _isPlay = false;
    _isWaiteRetry = false;
    _sceneChangeOK = false;
    
    _gameLayer = GameLayer::create();
    this->addChild(_gameLayer);
    
    
    _timerSp = Sprite::create("GameScene/timer/main_time_count_10.png");
    this->addChild(_timerSp);
    _timerSp->setPosition(Vec2(designResolutionSize.width/2,
                               designResolutionSize.height/1.3f)
                          );
    
    _startEffect = Effect::Create(this, this->getPosition(), EffectID::Ready);
    _startEffect->Start();
    
    
    _tapToRetry = Sprite::create("GameScene/tap_to_retry.png");
    _tapToRetry->setOpacity(0);
    _tapToRetry->setPosition(designResolutionSize/2);
    this->addChild(_tapToRetry);
    
    
    // タッチの処理の追加
    auto touchListener = cocos2d::EventListenerTouchAllAtOnce::create();//マルチタップ
    touchListener->onTouchesBegan = CC_CALLBACK_2(GameScene::onTouchesBegan, this);
    touchListener->onTouchesMoved = CC_CALLBACK_2(GameScene::onTouchesMoved, this);
    touchListener->onTouchesEnded = CC_CALLBACK_2(GameScene::onTouchesEnded, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    // キーボード
    auto keyListener = cocos2d::EventListenerKeyboard::create();
    keyListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
    keyListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);
    
    
    
    this->scheduleUpdate();
    
    //gameStart();
    
    return true;
}

void GameScene::update(float delta)
{
    if(!_isPlay && !_startEffect->GetIsRunning() && !_isWaiteRetry)
    {
        gameStart();
    }
    
    if(_frameCnt > 0 && _isPlay && _frameCnt % 60 == 0)
    {
        _time--;
        
        if(_time < 4)
        {
            _timerSp->runAction(Sequence::create(ScaleTo::create(0.2f, 0.5f),
                                                 EaseBounceOut::create(ScaleTo::create(0.3f, 1.5f)),
                                                 NULL
                                                 )
                                );
        }
        
        char str[128];
        sprintf(str, "GameScene/timer/main_time_count_%02d.png",_time);
        _timerSp->setTexture(str);
        log("time = %d",_time);
    }
    
    if(_time == 0 && _isPlay)
    {
        gameFinish();
    }
    
    if(_isPlay) _frameCnt++;
}

void GameScene::gameStart()
{
    _isPlay = true;
    _time = 10;
    _frameCnt = 0;
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/whistle.wav");
}

void GameScene::gameFinish()
{
    
    _isPlay = false;
    _gameLayer->gameFinish();
    _isWaiteRetry = true;
    
    _tapToRetry->runAction(Sequence::create(DelayTime::create(1.5f),
                                            FadeIn::create(1.0f),
                                            CallFunc::create([&](){_sceneChangeOK = true;}),
                                            NULL));
    
}

void GameScene::onTouchesBegan(const std::vector<Touch *> &touches, cocos2d::Event *unused_event)
{
}

void GameScene::onTouchesEnded(const std::vector<Touch *> &touches, cocos2d::Event *unused_event)
{
    if(_isWaiteRetry && _sceneChangeOK)
    {
        Director::getInstance()->replaceScene(GameScene::create());
    }
}

void GameScene::onTouchesMoved(const std::vector<Touch *> &touches, cocos2d::Event *unused_event)
{
    
}

void GameScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
 }

void GameScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    if(_isWaiteRetry && _sceneChangeOK)
    {
        Director::getInstance()->replaceScene(GameScene::create());
    }
 }
