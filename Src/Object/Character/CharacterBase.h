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

	//加速
	static constexpr float MOVE_ACC = 0.25f;

	//減速
	static constexpr float MOVE_DEC = 0.15f;

	//移動速度の最大値
	static constexpr float MAX_MOVE_SPEED = 3.5f;

	//最大ジャンプ力
	static constexpr float MAX_JUMP_POW = 8.0;
	static constexpr float DEATH_JUMP_POW = 6.0f;

	//重力
	static constexpr float GRAVITY = 0.25;

	//ジャンプのフレーム量
	static constexpr float INPUT_JUMP_FRAME = 4.0f;

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

protected:

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
	float moveMaxSpeed_;	//移動最大速度

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
	virtual void UpdateNone();
	virtual void UpdateActive();
	virtual void UpdateDeath();

	//移動(実際の座標移動)					
	void Move();				

	//加速に関する処理
	void Accele(float speed);		

	//減速に関する処理
	void Decelerate(float speed);	

	//重力をかける
	void AddGravity(void);				
	
	//ジャンプ
	void Jump(void);	
	
	//ジャンプ力の設定				
	void SetJumpPow(float pow);			

	//アニメーション処理
	void Animation();
};

