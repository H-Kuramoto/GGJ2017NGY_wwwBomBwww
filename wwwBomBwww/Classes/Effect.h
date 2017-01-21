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
		// ������V�[��
		cocos2d::Scene* m_currentScene;
		
		// �X�v���C�g
		cocos2d::Sprite* m_sprite;

		// �A�j���[�V����
		cocos2d::Animation* m_animation;

		cocos2d::Animate* m_animate;

		// ���W
		cocos2d::Vec2 m_position;

		// �J�n���Ɉ�x�����s���A�j���[�V����(���[�v���ɂ͍s��Ȃ�)
		cocos2d::Vector<cocos2d::FiniteTimeAction*> m_onceAction;

		// �J�n���ɍs���A�j���[�V����(���[�v���ɂ��s��)
		cocos2d::Vector<cocos2d::FiniteTimeAction*> m_startAction;

		// ���őO�ɍs���A�j���[�V����
		cocos2d::Vector<cocos2d::FiniteTimeAction*> m_endAction;

		// ���[�v�����邩
		bool m_loopFlg;
	public:
		virtual bool init();

		static Effect* Create(cocos2d::Scene* scene, EffectID id);

		void SetPosition(cocos2d::Vec2 position);

		void Start();

		void End();
};