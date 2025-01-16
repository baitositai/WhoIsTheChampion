#pragma once
#include "../../Application.h"
#include "../../Manager/ResourceManager.h"
#include "../../Common/Vector2.h"
#include "../../Common/Vector2F.h"

class CharacterBase
{
public:

	//キャラクター状態
	enum class STATE
	{
		NONE,
		ACTIVE,
		DEATH,
	};

	//アニメーション状態
	enum class ANIM_STATE
	{
		IDLE,
		RUN,
		JUMP,
		DOUBLE_JUMP,
		FALL,
		HIT,
		WALL_JUMP,
		MAX
	};

	//初期位置
	static constexpr float FIRST_POS_X = Application::SCREEN_HALF_X;
	static constexpr float FIRST_POS_Y = Application::SCREEN_SIZE_Y - 300;

	//プレイヤーサイズ
	static constexpr int SIZE_X = PLAYER_SIZE_X / PLAYER_NUM_X;
	static constexpr int SIZE_Y = PLAYER_SIZE_Y / PLAYER_NUM_Y;

	//移動速度
	static constexpr float MOVE_SPEED = 3.0f;

	//各種アニメーション数
	static constexpr int ANIM_NUM_IDLE = 11;
	static constexpr int ANIM_NUM_RUN = 12;
	static constexpr int ANIM_NUM_JUMP = 1;
	static constexpr int ANIM_NUM_DOUBLE_JUMP = 6;
	static constexpr int ANIM_NUM_FALL = 1;
	static constexpr int ANIM_NUM_HIT = 7;
	static constexpr int ANIM_NUM_WALL_JUMP = 5;

	//アニメーションスピード
	static constexpr float ANIM_SPEED = 0.3f;

	//アニメーション種類数
	static constexpr int ANIM_STATE_MAX = static_cast<int>(ANIM_STATE::MAX);

	CharacterBase();
	~CharacterBase() = default;

	virtual void Load();
	virtual	void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Release();

	//状態変更
	void ChangeState(const STATE state);

	//アニメーションの変更
	inline void ChangeAnimState(const ANIM_STATE state);

private:

	//状態
	STATE state_;

	//プレイヤー画像
	int* imgPlayer_;

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

	//アニメーション状態
	ANIM_STATE animState_;

	//アニメーションカウント
	float animCnt_;

	//アニメーション番号
	int animNum_;

	//アニメーション最大数
	int animMax_[ANIM_STATE_MAX];

	//アニメーションスピード
	float animSpeed_;

	// 状態管理(状態遷移時初期処理)
	std::map<STATE, std::function<void(void)>> stateChanges_;

	// 状態管理
	std::function<void(void)> stateUpdate_;

	//状態変更
	void ChangeNone();
	void ChangeActive();
	void ChangeDeath();

	//状態別更新処理
	void UpdateNone();
	void UpdateActive();
	void UpdateDeath();

	//アニメーション処理
	void Animation();
};

