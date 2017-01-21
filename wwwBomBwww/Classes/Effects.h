// ---------------------------------------
// File: Effects.h
// 
// Create: 2017/01/21
// 
// Author: Y.Watanabe
// ---------------------------------------
#pragma once

#include "cocos2d.h"

enum EffectID
{
	Ready,
	Go,
};

class Effects
{
	private:
		cocos2d::Sprite* m_sprite;
		cocos2d::FiniteTimeAction* m_startAction;
		cocos2d::FiniteTimeAction* m_endAction;

		Effects(cocos2d::Sprite* sprite, cocos2d::FiniteTimeAction* startAction, cocos2d::FiniteTimeAction* endAction);
	public:
		// static cocos2d::Sprite* create(EffectID id,float duration, const cocos2d::Vec2& pos, bool autoRelease = true);

		static Effects* create(EffectID id, bool autoRelease = true);

		void Start();
		void End();

		cocos2d::Sprite* GetSprite(){ return m_sprite; }
};

