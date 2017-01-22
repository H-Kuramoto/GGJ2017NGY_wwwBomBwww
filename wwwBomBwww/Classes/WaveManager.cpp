//
//  WaveManager.cpp
//  wwwBomBwww
//
//  Created by 蔵元隼人 on 2017/01/21.
//
//

#include "WaveManager.hpp"
#include "MultiResolution.h"
#include "GameLayer.hpp"

bool WaveManager::init()
{
    if(!Node::init())
    {
        return false;
    }
    
    for(int i = 0; i < WAVE_TILE_MAX; i++)
    {
        _waves[i] = WaveTile::create();
        
        // スプライト（コンテンツ）の大きさからスプライトの横幅を確定
        float contentW = _waves[i]->getContentSize().width;
        float scalX = WAVE_REGION_WIDTH / (contentW * WAVE_TILE_MAX);
        
        _waves[i]->setScaleX(scalX);
        _waves[i]->setPosition(Vec2( _waves[i]->getBoundingBox().size.width/2 + _waves[i]->getBoundingBox().size.width * i,
                                   0.0f)
                              );
        this->addChild(_waves[i]);
        
        _affectTimer[i] = 0;
        _isAffect[i]=false;
        _waveAffectTiming[i] = 0;
    }
    
    _power[0] = _power[1] = 0.0f;
    
    // タッチの処理の追加
    auto touchListener = cocos2d::EventListenerTouchAllAtOnce::create();//マルチタップ
    touchListener->onTouchesBegan = CC_CALLBACK_2(WaveManager::onTouchesBegan, this);
    touchListener->onTouchesMoved = CC_CALLBACK_2(WaveManager::onTouchesMoved, this);
    touchListener->onTouchesEnded = CC_CALLBACK_2(WaveManager::onTouchesEnded, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    // キーボード
    auto keyListener = cocos2d::EventListenerKeyboard::create();
    keyListener->onKeyPressed = CC_CALLBACK_2(WaveManager::onKeyPressed, this);
    keyListener->onKeyReleased = CC_CALLBACK_2(WaveManager::onKeyReleased, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);
    
    
    this->scheduleUpdate();
    
    return true;
}

void WaveManager::update(float delta)
{
    
    // タッチしてる間パワー溜める
    for(int i = 0; i < 2; i++)
    {
        if(_isTouching[i])
        {
            _power[i] += 0.1f;
            if(_power[i] > POWER_MAX) _power[i] = POWER_MAX;
            log("pow!!(%d)%f",i,_power[i]);
        }
    }
    
    
    
    for(int i = 0; i < WAVE_TILE_MAX; i++)
    {
        // 波の移動タイミングで次の波を作る
        //if(_isAffect[i] && _affectTimer[i] > _waveAffectTiming[i])
        if(_isAffect[i] && _affectTimer[i] > 5)
        {
            // その波が移動しないなら伝えない
            if(_waves[i]->_status.dir == WaveTile::MOVE_DIR::STOP) continue;
            
            // 移動方向で配列の要素数の確定
            int elem = i + (int)(_waves[i]->_status.dir);
            if(elem < 0 || elem >= WAVE_TILE_MAX) continue;
            
            // 伝え終わった波の初期化
            _isAffect[i] = false;
            _affectTimer[i] = 0;
            _waveAffectTiming[i] = 0;
            
            // 波を伝える
            _isAffect[elem] = true;
            _waveAffectTiming[elem] = makeAffectTiming(_waves[i]->_status.power);
            _waves[elem]->affectedByWaves(_waves[i]->_status);
        }
        
        // 波の伝えるタイミングのカウントアップ
        if(_isAffect[i])
        {
            _affectTimer[i]++;
        }
    }
    
    
    // 波とボムの当たり判定用
    {
        auto bomb = ((GameLayer*)(this->getParent()->getParent()))->_bomb;
        Rect bombRect = bomb->getRect();
        for(int i = 0; i < WAVE_TILE_MAX; i++)
        {
            if(_waves[i]->getBoundingBox().intersectsRect(bombRect))
            {
                bomb->moveX(_waves[i]->_status.dir, _waves[i]->_status.power);
            }
        }
    }
    
    
}

void WaveManager::startWave(int elem, WaveTile::MOVE_DIR dir, float power)
{
    if(elem > WAVE_TILE_MAX - 1) return;
    
    WaveTile::WaveStatus state;
    state.dir = dir;
    state.power = power;
    
    // 波を発生させる
    _waves[elem]->affectedByWaves(state);
    _waveAffectTiming[elem] = makeAffectTiming(power);
    _isAffect[elem] = true;
    _affectTimer[elem] = 0;
    
    
    log("affTiming[%d]",makeAffectTiming(power));

}

void WaveManager::onTouchesBegan(const std::vector<Touch *> &touches, cocos2d::Event *unused_event)
{
    for(auto toutch : touches)
    {
        if(toutch->getLocation().x < designResolutionSize.width/2)
        {
            _isTouching[0] = true;
            _toutchID[0] = toutch->getID();
        }
        else
        {
            _isTouching[1] = true;
            _toutchID[1] = toutch->getID();
        }
    }
}

void WaveManager::onTouchesEnded(const std::vector<Touch *> &touches, cocos2d::Event *unused_event)
{
    
    WaveTile::MOVE_DIR dir;
    int elem;
    float pow;

    for(auto toutch : touches)
    {
//        if(toutch->getID() >= 2) break;
        // 左
        if(toutch->getID() == _toutchID[0])
        {
            dir = WaveTile::MOVE_DIR::RGHITE;
            elem = 0;
            pow = _power[0];
            
            startWave(elem, dir, pow);

            _power[0] = 0.0f;
            _isTouching[0] = false;
            
            break;
        }
        
        if(toutch->getID() == _toutchID[1])
        {
            dir = WaveTile::MOVE_DIR::LEFT;
            elem = WAVE_TILE_MAX - 1;
            pow = _power[1];
            

            startWave(elem, dir, pow);

            _power[1] = 0.0f;
            _isTouching[1] = false;
            break;
        }
    }

    
        
        log("toutch");

    
}

void WaveManager::onTouchesMoved(const std::vector<Touch *> &touches, cocos2d::Event *unused_event)
{
    
}

void WaveManager::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    
    GameLayer *layer = (GameLayer*)(this->getParent()->getParent());
    
    if(keyCode == cocos2d::EventKeyboard::KeyCode::KEY_S)
    {
        _power[0] = 1.0f;
        _isTouching[0] = true;
        layer->_playerSp[0]->powerCharge();
    }
    if(keyCode == cocos2d::EventKeyboard::KeyCode::KEY_L)
    {
        _power[1] = 1.0f;
        _isTouching[1] = true;
        layer->_playerSp[1]->powerCharge();
    }

    
}

void WaveManager::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    
    WaveTile::MOVE_DIR dir;
    int elem;
    float pow;
    
    GameLayer *layer = (GameLayer*)(this->getParent()->getParent());
    
    if(keyCode == cocos2d::EventKeyboard::KeyCode::KEY_S) // 左のキャラ
    {
        dir = WaveTile::MOVE_DIR::RGHITE;
        elem = 0;
        pow = _power[0];
        
        startWave(elem, dir, pow);
        
        _power[0] = 0.0f;
        _isTouching[0] = false;

        _isTouching[0] = true;
        layer->_playerSp[0]->appearWave();
        
    }
    if(keyCode == cocos2d::EventKeyboard::KeyCode::KEY_L) // 右のキャラ
    {
        dir = WaveTile::MOVE_DIR::LEFT;
        elem = WAVE_TILE_MAX - 1;
        pow = _power[1];
        
        startWave(elem, dir, pow);
        
        _power[1] = 0.0f;
        _isTouching[1] = false;
        
        _isTouching[1] = true;
        layer->_playerSp[1]->appearWave();
    }

}

int WaveManager::makeAffectTiming(float wavePower)
{
    float n = 1 - (_power[1] / POWER_MAX);
    return  ceil((1 - n) * WAVE_AFFECT_TIMING_MAX + n * WAVE_AFFECT_TIMING_MIN - 1);
}

