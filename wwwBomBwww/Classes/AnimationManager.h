//-----------------------------------------------------------------------------------------------
// クラス概要 : 複数の画像を用いたアニメーション作成クラス
// 制作日時   : 2014.05.??
// 制作者名   : KuramotoHayato
//-----------------------------------------------------------------------------------------------


#ifndef __ANIMAITON_MANAGER_H__
#define __ANIMAITON_MANAGER_H__

#include "cocos2d.h"

using namespace cocos2d;

class AnimationManager
{
public:
	// 合成方法
	enum Blend
	{
		ADDITION,	//加算
		MULTIOPLICATION,	//乗算
		REVERSAL,	//反転
	};

	/**
		複数の画像ファイルでアニメーションの作成
		*	引数一覧
		*   fileName  ファイル名の雛形 xxxx_01%d.png のように連番画像ファイル名の雛形を指定する
		*   cacheName キャッシュに登録する名前　この名前で取り出しが出来る
		*   startNum  画像ファイルの連番開始数値
		*   endNum    画像ファイルの連番終了数値
		*   isReverse trueにすると 画像ファイルのアニメーションを頭から最後に最後から頭までの逆再生を加える
		*   duration  全フレームを表示する秒数の指定
		*/
	static void *addAnimationCachePluralFile(const char *fileName, const char *cacheName, int startNum, int endNum, bool isReverse, float duration);

	/**
	1つの画像ファイルでアニメーションの作成
	左上から右に1行ずつコマ送りする
	*	引数一覧
	*   cutFlameWidth 切り抜きコマ数(横)
	*	cutFlameHeight切り抜きコマ数(縦)
	*   cutRectSize   切り抜き矩形のサイズ
	*   fileName  ファイル名
	*   cacheName キャッシュに登録する名前　この名前で取り出しが出来る
	*   isReverse trueにすると 画像ファイルのアニメーションを頭から最後に最後から頭までの逆再生を加える
	*   duration  全フレームを表示する秒数の指定
	*/
	static void *addAnimationCacheOneFile(int cutFlameWidth, int cutFlameHeight, Size cutRectSize, const char *fileName, const char *cacheName, bool isReverse, float duration);

	/**
	1つの画像ファイルでアニメーションの作成
	左上から右に1行ずつコマ送りする
	*	引数一覧
	*   cutFlameWidth 切り抜きコマ数(横)
	*	cutFlameHeight切り抜きコマ数(縦)
	*   cutRectSize   切り抜き矩形のサイズ
	*   fileName  ファイル名
	*   cacheName キャッシュに登録する名前　この名前で取り出しが出来る
	*   isReverse trueにすると 画像ファイルのアニメーションを頭から最後に最後から頭までの逆再生を加える
	*   duration  全フレームを表示する秒数の指定
	*   blend	色値合成
	*/
	static void *addAnimationCacheOneFile(int cutFlameWidth, int cutFlameHeight, Size cutRectSize, Sprite* sp, const char *cacheName, bool isReverse, float duration, Blend blend);


	/**
	 * アニメーション再生
	 * 引数覧
	 * target    : アニメーションさせたいスプライト
	 * cacheName : セットしたアニメーションの名前
	 * tag		 : 0以外の数値を入れればアニメーションにタグを付ける。
	 * loop		 : 無限ループさせるか
	 */
	static void *runParaparaAnimation(Sprite *target, const char *cacheName, bool loop = true, int tag = 0);

	/**
	 ActionIntervalの取得
	 * 引数覧
	 * cacheName : セットしたアニメーションの名前
	 */
	static ActionInterval *getParaparaAction(const char *cacheName);


	/**
	tag管理によるパラパラアニメーションの停止。
	* 引数覧
	* target    : アニメーションストップさせたいスプライト
	* tag		: セットしたタグ
	*/

	static void *stopParaparaAnimation(Sprite *target, int tag);
};
#endif
