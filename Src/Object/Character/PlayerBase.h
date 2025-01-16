#pragma once
#include "../../framework.h"
#include "../../Application.h"
#include "../../Common/Vector2.h"
#include "../../Common/Vector2F.h"
#include "../../Manager/ResourceManager.h"
#include "../../Shader/PixelShader.h"

class PixelShader;

class PlayerBase
{
public:

	enum class DRAW_TYPE
	{
		NORMAL,			//通常
		DIFF_COLOR,		//色違い
		MAX
	};

	//初期位置
	static constexpr float FIRST_POS_X = Application::SCREEN_HALF_X;
	static constexpr float FIRST_POS_Y = Application::SCREEN_SIZE_Y - 300;

	//プレイヤーサイズ
	static constexpr int SIZE_X = PLAYER_RUN_SIZE_X / PLAYER_RUN_NUM_X;
	static constexpr int SIZE_Y = PLAYER_RUN_SIZE_Y / PLAYER_RUN_NUM_Y;

	//移動速度
	static constexpr float MOVE_SPEED = 3.0f;

	//アニメーションスピード
	static constexpr float ANIM_SPEED = 0.2f;

	//RUNアニメーション数
	static constexpr int ANIM_RUN_NUM = PLAYER_RUN_NUM_X * PLAYER_RUN_NUM_Y;

	//フォントサイズ
	static constexpr int FONT_SIZE = 64;

	//種類最大量
	static constexpr int TYPE_MAX = static_cast<int>(DRAW_TYPE::MAX);

	PlayerBase();
	~PlayerBase();

	void Load();
	void Init();
	virtual void Update();
	virtual void Draw();
	void Release();

private:

	//プレイヤー画像
	int *imgPlayer_;

	//プレイヤー拡大率
	float rate_;

	//プレイヤー回転
	float angle_;

	//座標
	Vector2F pos_;

	//プレイヤーサイズ
	Vector2 size_;

	//方向
	bool dir_;

	//移動スピード
	float moveSpeed_;

	//アニメーションカウント
	float animCnt_;

	//アニメーション番号
	int animNum_;

	//アニメーションスピード
	float animSpeed_;

	//描画種類
	DRAW_TYPE type_;

	//フォント
	int font_;

	//現在の種類名
	std::wstring name_;

	// 種類管理(種類遷移時初期処理)
	std::map<DRAW_TYPE, std::function<void(void)>> typeChanges_;

	// 種類管理
	std::function<void(void)> typeDraw_;

	//ピクセルシェーダー
	PixelShader& ps_;

	//状態変更
	void ChangeType(const DRAW_TYPE type);
	void ChangeTypeNormal();
	void ChangeTypeDiffColor();

	//種類別描画
	void NormalDraw();
	void DiffColorDraw();

	//種類名の描画
	void NameDraw();

	//アニメーション処理
	void Animation();

	//デバッグ描画
	void DebagDraw();
	
};

