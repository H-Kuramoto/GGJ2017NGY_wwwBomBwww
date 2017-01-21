// ---------------------------------------
// File: EffectEffect.cpp
// 
// Create: 2017/01/21
// 
// Author: Y.Watanabe
// ---------------------------------------

#include "Effect.h"

USING_NS_CC;

bool Effect::init()
{
	return true;
}

Effect* Effect::Create(Scene* scene, EffectID id)
{
	Effect* effect = new Effect();
	effect->m_animation = Animation::create();
	effect->m_currentScene = scene;

	// ���[�v�̓f�t�H���g�ł���悤��
	effect->m_loopFlg = true;

	// �������番��
	switch (id)
	{
		case ChargeEffect:
			// �X�v���C�g�A�j���[�V�����̓ǂݍ���
			for (int i = 1; i <= 15; i++)
			{
				char c[128];
				sprintf_s(c, "effects/charge_effect/charge_effect_%02d.png", i);
				effect->m_animation->addSpriteFrameWithFileName(c);
			}
			effect->m_animation->setDelayPerUnit(0.02f);

			effect->m_onceAction.pushBack(ScaleTo::create(0, 0));
			effect->m_startAction.pushBack(ScaleTo::create(effect->m_animation->getDuration() * 3.5f, 1));
			effect->m_endAction.pushBack(ScaleTo::create(effect->m_animation->getDuration(), 0));
			break;
		case BombExplode:
			// �X�v���C�g�A�j���[�V�����̓ǂݍ���
			for (int i = 1; i <= 33; i++)
			{
				char c[128];
				sprintf_s(c, "effects/bomb_explode/bomb_explode_%02d.png", i);
				effect->m_animation->addSpriteFrameWithFileName(c);
			}
			effect->m_animation->setDelayPerUnit(0.02f);
			effect->m_loopFlg = false;
			// effect->m_onceAction.pushBack(ScaleTo::create(0, 0));
			// effect->m_startAction.pushBack(ScaleTo::create(effect->m_animation->getDuration() * 3.5f, 1));
			// effect->m_endAction.pushBack(ScaleTo::create(effect->m_animation->getDuration(), 0));
			break;
		case Ready:
			effect->m_animation->addSpriteFrameWithFileName("ready.png");
			effect->m_animation->addSpriteFrameWithFileName("go.png");
			effect->m_animation->setDelayPerUnit(0.6f);
			effect->m_loopFlg = false;
			effect->m_onceAction.pushBack(
				Sequence::create(
					Place::create(Vec2(1920 + 400, 400)),
					MoveTo::create(0.6f, Vec2(1920 / 2, 400)),
					nullptr));
			effect->m_onceAction.pushBack(
				Spawn::create(
					FadeOut::create(0.6f),
					ScaleTo::create(0.6f, 2.0f),
					nullptr));
			break;
		case Win:
			effect->m_animation->addSpriteFrameWithFileName("win.png");
			effect->m_animation->setDelayPerUnit(1);
			effect->m_onceAction.pushBack(
				Sequence::create(
					ScaleTo::create(0,0),
					ScaleTo::create(0.4f, 1.0f),
					nullptr));
			break;
		case Lose:
			break;
	}

	// �����܂ŕ���

	// �A�j���[�V�����������Ȃ��悤�ɂ���
	effect->m_animation->retain();

	return effect;
}

void Effect::SetPosition(Vec2 position)
{
	m_position = position;
}

void Effect::Start()
{
	if(m_sprite != nullptr)
		return;

	m_sprite = Sprite::create();

	m_sprite->setPosition(m_position);

	// �A�j���[�V�����Ԋu
	m_animation->setRestoreOriginalFrame(false);

	if(m_onceAction.size() > 0)
	// �J�n���Ɉ�x�����s���A�j���[�V����
	m_sprite->runAction(
		Sequence::create(m_onceAction)
	);

	if (m_startAction.size() > 0)
	// �J�n���ɍs���A�j���[�V����(���[�v���ɂ��s��)
	m_sprite->runAction(
		RepeatForever::create(
			Sequence::create(m_startAction)
			)
		);

	if(m_loopFlg)
	// �X�v���C�g�A�j���[�V����
	m_sprite->runAction(
		RepeatForever::create(
			Animate::create(m_animation)
			)
		);

	else
		m_sprite->runAction(
			Sequence::create(
				Animate::create(m_animation),
				CallFunc::create([&]()
				{
					m_sprite->stopAllActions();
					m_sprite->removeFromParent();
					m_sprite = nullptr;
				})
				,nullptr)
			);
			

	m_currentScene->addChild(m_sprite, INT_MAX);

}

void Effect::End()
{
	if(m_sprite == nullptr)
		return;

	if (m_endAction.size() > 0)
	m_sprite->runAction(
		Sequence::create(
			Sequence::create(m_endAction),
			CallFunc::create([&](){
				m_sprite->stopAllActions();
				m_sprite->removeFromParent();
				m_sprite = nullptr;
			}),
			nullptr)
		);
}

/*
Sprite* EffectManager::EffectPurified(Point location, std::string name, bool loop)
{
	// ���[�v��
	Animation* animation = Animation::create();
	for (int i = 1; i <= 15; i++)
	{
		char c[128];
		sprintf_s(c, "effects/charge_effect/charge_effect_%02d.png", i);
		animation->addSpriteFrameWithFileName(c);
	}

	// �A�j���[�V�����Ԋu
	animation->setDelayPerUnit(0.02f);
	animation->setRestoreOriginalFrame(true);

	Animate *animateAction = Animate::create(animation);

	auto sprite2 = cocos2d::Sprite::create();
	if (loop)
	{
		sprite2->runAction(RepeatForever::create(animateAction));
	}
	else
	{
		sprite2->runAction(
			Sequence::create(animateAction,
				CallFunc::create(
					[sprite2]()
		{
			sprite2->removeFromParentAndCleanup(true);
		}), NULL));
	}
	sprite2->setPosition(location);
	currentScene->addChild(sprite2, INT_MAX);
	return sprite2;
}
*/