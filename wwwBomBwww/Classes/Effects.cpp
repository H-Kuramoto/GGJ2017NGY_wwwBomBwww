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

	// 画像の格納
	Sprite* effect = nullptr;

	// アクションの格納先
	Vector<FiniteTimeAction*> action;

	// 画像の読み込み
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

	// 座標を設定
	effect->setPosition(pos);

	FiniteTimeAction* fAction = nullptr;

	// アクションが終わったら解放するか
	if(autoRelease)
		action.pushBack(RemoveSelf::create());

	fAction = Sequence::create(action);
	// アクションの実行
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

	// 自動解放するか
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