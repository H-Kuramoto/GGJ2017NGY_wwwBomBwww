// ---------------------------------------
// File: Effects.cpp
// 
// Create: 2017/01/21
// 
// Author: Y.Watanabe
// ---------------------------------------

#include "Effects.h"

USING_NS_CC;

/*
Sprite* Effects::create(EffectID id, float duration, const cocos2d::Vec2& pos, bool autoRelease)
{

	// �摜�̊i�[
	Sprite* effect = nullptr;

	// �A�N�V�����̊i�[��
	Vector<FiniteTimeAction*> action;

	// �摜�̓ǂݍ���
	switch (id)
	{
		case Ready:
			effect = Sprite::create("ready.png");
			action.pushBack(ScaleBy::create(duration, 1.5f));
			action.pushBack(ScaleBy::create(duration, 0.5f));
			break;
		case Go:
			effect = Sprite::create("go.png");
			action.pushBack(ScaleBy::create(duration, 1.5f));
			break;
	}

	// ���W��ݒ�
	effect->setPosition(pos);

	FiniteTimeAction* fAction = nullptr;

	// �A�N�V�������I������������邩
	if(autoRelease)
		action.pushBack(RemoveSelf::create());

	fAction = Sequence::create(action);
	// �A�N�V�����̎��s
	effect->runAction(fAction);

	return effect;
}*/

Effects::Effects(Sprite* sprite, FiniteTimeAction* startAction, FiniteTimeAction* endAction)
{
	m_sprite = sprite;
	m_startAction = startAction;
	m_endAction = endAction;
}

Effects* Effects::create(EffectID id, bool autoRelease)
{
	Vector<FiniteTimeAction*> action;
	Sprite* sprite = nullptr;

	switch (id)
	{
		case Ready:
			sprite = Sprite::create("ready.png");
			action.pushBack(ScaleBy::create(0.8f, 1.5f));
			action.pushBack(ScaleBy::create(0.5f, 0.5f));
			break;
		case Go:
			break;
	}

	// ����������邩
	if(autoRelease)
		action.pushBack(RemoveSelf::create());

	return new Effects(sprite, Sequence::create(action), nullptr);
}

void Effects::Start()
{
	m_sprite->runAction(m_startAction);
}

void Effects::End()
{
	if(m_endAction)
		m_sprite->runAction(m_endAction);
}