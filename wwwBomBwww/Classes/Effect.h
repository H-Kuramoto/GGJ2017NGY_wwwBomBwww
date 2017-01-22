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
	// お邪魔の注意喚起
	// y座標は無視されます
	Caution,
};

class Effect
{
	private:
		// 所属先ノード
		cocos2d::Node* m_currentScene;
		
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

		// アニメーションが実行中か
		bool m_isRunning;

		// Zorder
		int m_zOrder;
	public:
		virtual bool init();

		static Effect* Create(cocos2d::Node* node, cocos2d::Vec2 position, EffectID id);

		/// <summary>
		///	座標の設定
		/// </summary>
		/// <param name="position"></param>
		void SetPosition(cocos2d::Vec2 position)
		{
			m_position = position;
		}

		/// <summary>
		/// ZOrderの設定
		/// </summary>
		/// <param name="order"></param>
		void SetZOrder(int order)
		{
			m_zOrder = order;
		}

		bool GetIsRunning()
		{
			return m_isRunning;
		}

		void Start();

		void End();

	private:
		// エフェクト作成関数
		void CreateEffect(EffectID id);
};