#pragma once
#include "../framework.h"
#include "../Utility/StaticSingleton.h"
#include "Resource.h"

// オムレツ走る画像
constexpr int OMU_RUN_NUM_X = 6;
constexpr int OMU_RUN_NUM_Y = 1;
constexpr int OMU_RUN_SIZE_X = 1080 / OMU_RUN_NUM_X;
constexpr int OMU_RUN_SIZE_Y = 240 / OMU_RUN_NUM_Y;

//プレイヤー画像
constexpr int PLAYER_NUM_X = 12;
constexpr int PLAYER_NUM_Y = 7;
constexpr int PLAYER_SIZE_X = 600 / PLAYER_NUM_X;
constexpr int PLAYER_SIZE_Y = 350 / PLAYER_NUM_Y;

class ResourceManager :
	public StaticSingleton<ResourceManager>
{

public:

	// リソース名
	enum class SRC
	{
		TITLE_LOGO,
		OMU_RUN,
		PLAYER_01,
		PLAYER_02,
		PLAYER_03,
		PLAYER_04,
	};

	// 初期化
	void Init(void);

	// 解放(シーン切替時に一旦解放)
	void Release(void);

	// リソースの完全破棄
	void Destroy(void);

	// リソースのロード
	Resource Load(SRC src);

	// リソースの複製ロード(モデル用)
	int LoadModelDuplicate(SRC src);

private:

	//シングルトンの生成
	THIS_CLASS_IS_STATIC_SINGLETON(ResourceManager);

	// リソース管理の対象
	std::map<SRC, Resource> resourcesMap_;

	// 読み込み済みリソース
	std::map<SRC, Resource*> loadedMap_;

	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	ResourceManager(void);

	// デストラクタも同様
	~ResourceManager(void) = default;

	// 内部ロード
	Resource* _Load(SRC src);

};

