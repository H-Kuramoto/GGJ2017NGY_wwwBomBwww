// ---------------------------------------
// File: TitleScene.cpp
// 
// Create: 2017/01/21
// 
// Author: Y.Watanabe
// ---------------------------------------

#include "TitleScene.h"
// #include <ui/UIButton.h>
#include "GameScene.hpp"

USING_NS_CC;
// USING_NS_CC_EXT;

bool TitleScene::init()
{
	// 基底クラスの初期化
	if (!Scene::init())
	{
		// 基底クラスの初期化が失敗なら、異常終了
		return false;
	}

	// 画面サイズ
	Size windowSize = _director->getVisibleSize();

	// 背景の作成、追加
	Sprite* background = Sprite::create("title/title_back.png");
	background->setZOrder(1);
	background->setPosition(Vec2(windowSize.width / 2, windowSize.height / 2));
	addChild(background);

	// スタートボタンの作成、追加
	//
	//ui::Button* startButton = ui::Button::create("title/start_button.png");
	//startButton->setPosition(Vec2(windowSize.width / 2, 300));
	//addChild(startButton);

	//// スタートボタンのアクション
	//startButton->addTouchEventListener([&](Ref* ref, ui::Widget::TouchEventType eventType)
	//{
	//	// ボタンが離されたら
	//	if (eventType == ui::Widget::TouchEventType::ENDED)
	//	{
	//		// 次のシーンの作成
	//		Scene* nextScene = GameScene::create();
	//		nextScene = TransitionFade::create(1.0f, nextScene, Color3B::BLACK);

	//		// 次のシーンに移動
	//		_director->replaceScene(nextScene);
	//	}
	//});

	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = ([&](Touch* touch, Event* pEvent)
	{
		Vec2 touchPos = touch->getLocation();

		if(effect == nullptr)
			effect = Effect::Create(this, touchPos, EffectID::Ready);

		effect->SetPosition(touchPos);
		effect->SetZOrder(0);
		effect->Start();
		return true;
	});

	listener->onTouchEnded = ([&](Touch* touch, Event* pEvent)
	{
		log("touch ended");
		effect->End();
	});
	_director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}
