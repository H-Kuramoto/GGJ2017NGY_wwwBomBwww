// ---------------------------------------
// File: Effect.h
// 
// Create: 2017/01/21
// 
// Author: Y.Watanabe
// ---------------------------------------
#pragma once

#include "cocos2d.h"

enum EffectID
{
	ChargeEffect,
	BombExplode,
	Ready,
	Win,
	Lose,
};

class Effect
{
	private:
		// 所属先シーン
		cocos2d::Scene* m_currentScene;
		
		// スプライト
		cocos2d::Sprite* m_sprite;

		// アニメーション
		cocos2d::Animation* m_animation;

		cocos2d::Animate* m_animate;

		// 座標
		cocos2d::Vec2 m_position;

		// 開始時に一度だけ行うアニメーション(ループ時には行わない)
		cocos2d::Vector<cocos2d::FiniteTimeAction*> m_onceAction;

		// 開始時に行うアニメーション(ループ時にも行う)
		cocos2d::Vector<cocos2d::FiniteTimeAction*> m_startAction;

		// 消滅前に行うアニメーション
		cocos2d::Vector<cocos2d::FiniteTimeAction*> m_endAction;

		// ループさせるか
		bool m_loopFlg;
	public:
		virtual bool init();

		static Effect* Create(cocos2d::Scene* scene, EffectID id);

		void SetPosition(cocos2d::Vec2 position);

		void Start();

		void End();
};