// ---------------------------------------
// File: TitleScene.cpp
// 
// Create: 2017/01/21
// 
// Author: Y.Watanabe
// ---------------------------------------

#include "TitleScene.h"
#include <ui\UIButton.h>

USING_NS_CC;

bool TitleScene::init()
{
	// ���N���X�̏�����
	if (!Scene::init())
	{
		// ���N���X�̏����������s�Ȃ�A�ُ�I��
		return false;
	}
	
	// ��ʃT�C�Y
	Size windowSize = _director->getVisibleSize();

	// �w�i�̍쐬�A�ǉ�
	Sprite* background = Sprite::create("title/title_back.png");
	background->setPosition(Vec2(windowSize.width / 2, windowSize.height / 2));
	addChild(background);

	// �X�^�[�g�{�^���̍쐬�A�ǉ�
	ui::Button* startButton = ui::Button::create("title/start_button.png");
	startButton->setPosition(Vec2(windowSize.width / 2, 300));
	addChild(startButton);

	// �X�^�[�g�{�^���̃A�N�V����
	startButton->addTouchEventListener([&](Ref* ref, ui::Widget::TouchEventType eventType)
	{
		// �{�^���������ꂽ��
		if (eventType == ui::Widget::TouchEventType::ENDED)
		{
			// ���̃V�[���̍쐬
			Scene* nextScene = TitleScene::create();
			nextScene = TransitionFade::create(1.0f, nextScene, Color3B::BLACK);

			// ���̃V�[���Ɉړ�
			_director->replaceScene(nextScene);
		}
	});

	return true;
}
