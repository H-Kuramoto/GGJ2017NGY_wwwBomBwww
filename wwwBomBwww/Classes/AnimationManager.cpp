//-----------------------------------------------------------------------------------------------
// クラス概要 : 複数の画像を用いたアニメーション作成クラス
// 制作日時   : 2014.05.??
// 制作者名   : KuramotoHayato
//-----------------------------------------------------------------------------------------------

#include "AnimationManager.h"


// アニメーションの保存
void *AnimationManager::addAnimationCachePluralFile(const char *fileName, const char *cacheName, int startNum, int endNum, bool isReverse, float duration)
{

	// アニメーションはシングルトン
	AnimationCache *animationCache = AnimationCache::getInstance();
	// アニメーションフレームを管理するクラス
	Animation *animation = Animation::create();

	// アニメーションのコマ数の記憶用
	int spCnt = 0;


	// あえて後ろの番号からアニメーションさせたい人に対応
	if (startNum < endNum)
	{
		// アニメーションのコマ分繰り返す
		for (int i = startNum; i < endNum + 1; i++)
		{
			// ファイル名を生成
			char szImageFileName[128] = { 0 };
			sprintf(szImageFileName, fileName, i);

			// アニメーション フレーム画像を追加
			animation->addSpriteFrameWithFileName(szImageFileName);
			// アニメーションのコマ数を追加
			spCnt++;
		}
		// 用意した画像を反対の順番で格納する
		if (isReverse == true)
		{
			for (int i = endNum - 1; i >= startNum; i--)
			{
				//ファイル名を生成
				char szImageFileName[128] = { 0 };
				sprintf(szImageFileName, fileName, i);

				// アニメーション フレームに画像を追加
				animation->addSpriteFrameWithFileName(szImageFileName);
				// アニメーションのコマ数を追加
				spCnt++;
			}
		}
	}
	else
	{
		// アニメーションのコマ分繰り返す
		for (int i = startNum; i >= endNum; i--)
		{
			// ファイル名を生成
			char szImageFileName[128] = { 0 };
			sprintf(szImageFileName, fileName, i);

			// アニメーション フレーム画像を追加
			animation->addSpriteFrameWithFileName(szImageFileName);

			// アニメーションのコマ数を追加
			spCnt++;
		}
		// 用意した画像を反対の順番で格納する
		if (isReverse == true)
		{
			for (int i = endNum; i <= startNum; i++)
			{
				//ファイル名を生成
				char szImageFileName[128] = { 0 };
				sprintf(szImageFileName, fileName, i);

				// アニメーション フレームに画像を追加
				animation->addSpriteFrameWithFileName(szImageFileName);

				// アニメーションのコマ数を追加
				spCnt++;
			}
		}

	}



	// 引数の"duration"秒間で全フレームを表示
	int frameCnt = spCnt;
	animation->setDelayPerUnit(duration / frameCnt);

	// 全フレーム表示後に最初のフレームに戻る設定
	animation->setRestoreOriginalFrame(true);

	// 出来たアニメーションをキャッシュに登録
	animationCache->addAnimation(animation, cacheName);


	return 0;

}




void *AnimationManager::addAnimationCacheOneFile(int cutFlameWidth, int cutFlameHeight, Size cutRectSize, const char *fileName, const char *cacheName, bool isReverse, float duration)
{

	// アニメーションはシングルトン
	AnimationCache *animationCache = AnimationCache::getInstance();
	// アニメーションフレームを管理するクラス
	Animation *animation = Animation::create();

	// texture2Dセット
	Texture2D *tex = new Texture2D();
	Image img;
	img.initWithImageFile(fileName);
	// セット
	//tex = texbase->getTexture();
	tex->initWithImage(&img);
	// 開始点から1行ずつ保存
	for (int y = 0; y < cutFlameHeight; y++)
	{
		for (int x = 0; x < cutFlameWidth; x++)
		{
			// 切り抜き用のRect生成
			Rect rect(
				x * cutRectSize.width,
				y * cutRectSize.height,
				cutRectSize.width,
				cutRectSize.height
				);

			// アニメーション フレーム画像を追加
			animation->addSpriteFrameWithTexture(tex, rect);

		}
	}
	// 逆再生の追加
	if (isReverse == true)
	{
		for (int y = cutFlameHeight - 1; y >= 0; y--)
		{
			for (int x = cutFlameWidth - 1; x >= 0; x--)
			{
				Rect rect(
					x * cutRectSize.width,
					y * cutRectSize.height,
					cutRectSize.width,
					cutRectSize.height
					);

				// アニメーション フレーム画像を追加
				animation->addSpriteFrameWithTexture(tex, rect);
				
			}
		}
	}

	// 引数の"duration"秒間で全フレームを表示
	int rectNumMax = cutFlameWidth * cutFlameHeight;
	animation->setDelayPerUnit(duration / rectNumMax);

	// 全フレーム表示後に最初のフレームに戻る設定
	animation->setRestoreOriginalFrame(true);

	// 出来たアニメーションをキャッシュに登録
	animationCache->addAnimation(animation, cacheName);

	return 0;
}



void *AnimationManager::addAnimationCacheOneFile(int cutFlameWidth, int cutFlameHeight, Size cutRectSize, Sprite* sp, const char *cacheName, bool isReverse, float duration, Blend blend)
{

	// アニメーションはシングルトン
	AnimationCache *animationCache = AnimationCache::getInstance();
	// アニメーションフレームを管理するクラス
	Animation *animation = Animation::create();

	// 合成用のBlendFunc
	BlendFunc blendFunc;

	// blendの方法
	switch (blend)
	{
	case ADDITION:
		blendFunc.src = GL_SRC_ALPHA;
		blendFunc.dst = GL_ONE;
		break;
	case MULTIOPLICATION:
		blendFunc.src = GL_ZERO;
		blendFunc.dst = GL_SRC_COLOR;
		break;
	case REVERSAL:
		blendFunc.src = GL_ONE_MINUS_DST_COLOR;
		blendFunc.dst = GL_ZERO;
		break;
	}

	// texture2Dセット
	/* Image型のinitWithImageFileを使うと
	// cocos2d: fullPathForFilename: No file found at /cc_2x2_white_image. Possible missing file.
	// Run - Time Check Failure #3 - The variable 'tex' is being used without being initialized.
	// というエラーが出るから一旦保留
	*/
	// Texture2Dを吸い出すためだけにSpriteを作る
	//Sprite *texbase = Sprite::create(fileName);
	// Blend
	sp->setBlendFunc(blendFunc);
	Texture2D *tex;
	// セット
	tex = sp->getTexture();

	// 開始点から1行ずつ保存
	for (int y = 0; y < cutFlameHeight; y++)
	{
		for (int x = 0; x < cutFlameWidth; x++)
		{
			// 切り抜き用のRect生成
			Rect rect(
				x * cutRectSize.width,
				y * cutRectSize.height,
				cutRectSize.width,
				cutRectSize.height
				);

			// アニメーション フレーム画像を追加
			animation->addSpriteFrameWithTexture(tex, rect);

		}
	}
	// 逆再生の追加
	if (isReverse == true)
	{
		for (int y = cutFlameHeight - 1; y >= 0; y--)
		{
			for (int x = cutFlameWidth - 1; x >= 0; x--)
			{
				Rect rect(
					x * cutRectSize.width,
					y * cutRectSize.height,
					cutRectSize.width,
					cutRectSize.height
					);

				// アニメーション フレーム画像を追加
				animation->addSpriteFrameWithTexture(tex, rect);

			}
		}
	}

	// 引数の"duration"秒間で全フレームを表示
	int rectNumMax = cutFlameWidth * cutFlameHeight;
	animation->setDelayPerUnit(duration / rectNumMax);

	// 全フレーム表示後に最初のフレームに戻る設定
	animation->setRestoreOriginalFrame(true);

	// 出来たアニメーションをキャッシュに登録
	animationCache->addAnimation(animation, cacheName);

	return 0;
}



void *AnimationManager::runParaparaAnimation(Sprite *target, const char *cacheName,bool loop, int tag)
{
	AnimationCache *animationCache = AnimationCache::sharedAnimationCache();
	// キャッシュから指定されたアニメーションを引っ張ってくる
	Animation *animation = animationCache->animationByName(cacheName);
	
	// アニメーションからアクション作成
	Animate *paraani = Animate::create(animation);



	// アニメーションの作成
	if (loop == true)
	{
		RepeatForever *repeatForever = RepeatForever::create(paraani);
		// tagがデフォルトと変っていたらセットする
		if (tag != 0)
		{
			repeatForever->setTag(tag);
		}
		target->runAction(repeatForever);
	}
	else
	{
		// tagがデフォルトと変っていたらセットする
		if (tag != 0)
		{
			paraani->setTag(tag);
		}
		target->runAction(paraani);

	}
	return 0;
}

ActionInterval *AnimationManager::getParaparaAction(const char *cacheName)
{
	AnimationCache *animationCache = AnimationCache::sharedAnimationCache();
	// キャッシュから指定されたアニメーションを引っ張ってくる
	Animation *animation = animationCache->animationByName(cacheName);
	ActionInterval *parapaAction = Animate::create(animation);
	
	return parapaAction;
}

void *AnimationManager::stopParaparaAnimation(Sprite *target, int tag)
{
	target->stopActionByTag(tag);

	return 0;
}
