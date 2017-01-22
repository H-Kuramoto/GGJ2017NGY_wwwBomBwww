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

Effect* Effect::Create(Node* node, Vec2 position, EffectID id )
{
	Effect* effect = new Effect();
	effect->m_animation = Animation::create();
	effect->m_currentScene = node;
	effect->SetPosition(position);

	// ループはデフォルトでするように
	effect->m_loopFlg = true;

	// エフェクトの作成
	effect->CreateEffect(id);

	// アニメーションが消えないようにする
	effect->m_animation->retain();

	// 生成したエフェクトの返却
	return effect;
}

void Effect::Start()
{
	if(m_sprite != nullptr)
		return;

	m_sprite = Sprite::create();

	m_sprite->setPosition(m_position);

	// アニメーション間隔
	m_animation->setRestoreOriginalFrame(false);

	if(m_onceAction.size() > 0)
		// 開始時に一度だけ行うアニメーション
		m_sprite->runAction(
			Sequence::create(m_onceAction)
		);

	if (m_startAction.size() > 0)
		// 開始時に行うアニメーション(ループ時にも行う)
		m_sprite->runAction(
			RepeatForever::create(
				Sequence::create(m_startAction)
				)
			);

	if(m_loopFlg)
		// スプライトアニメーション
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
			
	// アニメーションの実行フラグを立てる
	m_isRunning = true;

	m_currentScene->addChild(m_sprite, m_zOrder);
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

void Effect::CreateEffect(EffectID id)
{
	switch (id)
	{
		case ChargeEffect:
			// スプライトアニメーションの読み込み
			for (int i = 1; i <= 15; i++)
			{
				char c[128];
				sprintf(c, "effects/charge_effect/charge_effect_%02d.png", i);
				m_animation->addSpriteFrameWithFileName(c);
			}
			m_animation->setDelayPerUnit(0.02f);

			m_onceAction.pushBack(ScaleTo::create(0, 0));
			m_startAction.pushBack(ScaleTo::create(m_animation->getDuration() * 3.5f, 1));
			m_endAction.pushBack(ScaleTo::create(m_animation->getDuration(), 0));
			break;
		case BombExplode:
			// スプライトアニメーションの読み込み
			for (int i = 1; i <= 33; i++)
			{
				char c[128];
				sprintf(c, "effects/bomb_explode/bomb_explode_%02d.png", i);
				m_animation->addSpriteFrameWithFileName(c);
			}
			m_animation->setDelayPerUnit(0.02f);
			m_loopFlg = false;
			break;
		case Ready:
			m_animation->addSpriteFrameWithFileName("ready.png");
			m_animation->addSpriteFrameWithFileName("go.png");
			m_animation->setDelayPerUnit(1.4f);
			m_loopFlg = false;
			m_onceAction.pushBack(
				Sequence::create(
					Place::create(Vec2(1920 + 400, 400)),
					MoveTo::create(0.6f, Vec2(1920 / 2, 400)),
					DelayTime::create(0.8f),
					nullptr));
			m_onceAction.pushBack(
				Spawn::create(
					FadeOut::create(0.8f),
					ScaleTo::create(0.8f, 2.0f),
					nullptr));
			break;
		case Win:
			m_animation->addSpriteFrameWithFileName("win.png");
			m_animation->setDelayPerUnit(1);
			m_onceAction.pushBack(
				ScaleTo::create(0, 0)
				);
			m_onceAction.pushBack(
				ScaleTo::create(0.4f, 1.0f)
				);
			m_startAction.pushBack(
				EaseInOut::create(
					Sequence::create(
						ScaleTo::create(0.5f, 0.5f),
						ScaleTo::create(0.5f, 1.0f),
						nullptr),
					1.5f)
				);
			break;
		case Lose:
			m_animation->addSpriteFrameWithFileName("lose.png");
			m_animation->setDelayPerUnit(1);
			m_onceAction.pushBack(
				Place::create(Vec2(m_position.x, 1200))
				);
			m_onceAction.pushBack(
				EaseOut::create(
					MoveTo::create(2.0f, m_position),
					1.5f)
				);
			m_startAction.pushBack(
				EaseInOut::create(
					Sequence::create(
						ScaleTo::create(0.5f, 0.8f),
						ScaleTo::create(0.5f, 1.0f),
						nullptr),
					1.5f)
				);
			break;
		case Caution:
			m_animation->addSpriteFrameWithFileName("ojama_caution.png");
			m_animation->setDelayPerUnit(1);
			m_onceAction.pushBack(
				FadeOut::create(0)
				);
			m_onceAction.pushBack(
				Place::create(Vec2(m_position.x, 920))
				);
			m_onceAction.pushBack(
				Spawn::create(
					EaseInOut::create(
						Repeat::create(
							Sequence::create(
								ScaleTo::create(0.06f, 0, 1),
								ScaleTo::create(0.06f, 1, 1),
								nullptr
								),
							1),
						1.5f),
					FadeIn::create(0.12f),
					nullptr)
				);
			m_onceAction.pushBack(
				EaseBackOut::create(
					Sequence::create(
						ScaleTo::create(0.2f, 1.5f),
						ScaleTo::create(0.2f, 1.0f),
						nullptr)
					)
				);
			break;
	}

	// ループしないアニメーションの末尾に実行フラグを折るアクションを追加
	if (m_loopFlg != true)
	{
		m_onceAction.pushBack(CallFunc::create([&]()
		{
			m_isRunning = false;
		}));
	}

}
