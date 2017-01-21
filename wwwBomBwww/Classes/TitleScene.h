// ---------------------------------------
// File: TitleScene.h
// 
// Create: 2017/01/21
// 
// Author: Y.Watanabe
// ---------------------------------------
#pragma once

#include "cocos2d.h"
#include "Effect.h"

class TitleScene : public cocos2d::Scene
{
	private:
		Effect* effect;

	public:
		CREATE_FUNC(TitleScene);

		bool init();
};
