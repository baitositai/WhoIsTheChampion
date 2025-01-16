#include "../../framework.h"
#include "CharacterBase.h"

CharacterBase::CharacterBase()
{
	angle_ = -1.0f;
	animCnt_ = -1.0f;
	for (int i = 0; i < ANIM_STATE_MAX; i++) { animMax_[i] = -1; }
	animNum_ = -1;
	animSpeed_ = -1.0f;
	animState_ = ANIM_STATE::MAX;
	dir_ = false;
	moveSpeed_ = -1.0f;
	rate_ = -1.0f;
	state_ = STATE::NONE;

	//分割画像初期化
	int value = -1;
	imgPlayer_ = &value;

	//各種変更処理の格納
	stateChanges_.emplace(STATE::NONE, std::bind(&CharacterBase::ChangeNone, this));
	stateChanges_.emplace(STATE::ACTIVE, std::bind(&CharacterBase::ChangeActive, this));
	stateChanges_.emplace(STATE::DEATH, std::bind(&CharacterBase::ChangeDeath, this));
}

void CharacterBase::Load()
{
	//画像読み込み
	imgPlayer_ = ResourceManager::GetInstance().Load(
		ResourceManager::SRC::PLAYER_01).handleIds_;
}

void CharacterBase::Init()
{
#pragma region ステータス設定
	//初期位置
	pos_ = { FIRST_POS_X, FIRST_POS_Y };

	//プレイヤー拡大率
	rate_ = 1.0f;

	//プレイヤー回転
	angle_ = 0.0f;

	//プレイヤーサイズ
	size_ = { SIZE_X, SIZE_Y };

	//方向
	dir_ = false;

	//移動スピード
	moveSpeed_ = MOVE_SPEED;
#pragma endregion 

#pragma region アニメーション設定
	//アニメーションカウント
	animCnt_ = 0.0f;

	//アニメーション番号
	animNum_ = 0;

	//アニメーションスピード
	animSpeed_ = ANIM_SPEED;

	//アニメーション最大数
	animMax_[static_cast<int>(ANIM_STATE::IDLE)] = ANIM_NUM_IDLE;
	animMax_[static_cast<int>(ANIM_STATE::RUN)] = ANIM_NUM_RUN;
	animMax_[static_cast<int>(ANIM_STATE::JUMP)] = ANIM_NUM_JUMP;
	animMax_[static_cast<int>(ANIM_STATE::DOUBLE_JUMP)] = ANIM_NUM_DOUBLE_JUMP;
	animMax_[static_cast<int>(ANIM_STATE::FALL)] = ANIM_NUM_FALL;
	animMax_[static_cast<int>(ANIM_STATE::HIT)] = ANIM_NUM_HIT;
	animMax_[static_cast<int>(ANIM_STATE::WALL_JUMP)] = ANIM_NUM_WALL_JUMP;
#pragma endregion 

	//初期状態
	ChangeState(STATE::ACTIVE);

	//初期アニメーション状態
	ChangeAnimState(ANIM_STATE::IDLE);
}

void CharacterBase::Update()
{
	stateUpdate_();
}

void CharacterBase::Draw()
{
	DrawRotaGraph(
		pos_.x,
		pos_.y,
		rate_,
		angle_,
		imgPlayer_[animNum_],
		true,
		dir_
	);
}

void CharacterBase::Release()
{
}

void CharacterBase::ChangeState(const STATE state)
{
	// 状態受け取り
	state_ = state;

	// 各状態遷移の初期処理
	stateChanges_[state_]();
}

inline void CharacterBase::ChangeAnimState(const ANIM_STATE state)
{
	//状態受け取り
	animState_ = state;
}

void CharacterBase::ChangeNone()
{
	stateUpdate_ = std::bind(&CharacterBase::UpdateNone, this);
}

void CharacterBase::ChangeActive()
{
	stateUpdate_ = std::bind(&CharacterBase::UpdateActive, this);
}

void CharacterBase::ChangeDeath()
{
	stateUpdate_ = std::bind(&CharacterBase::UpdateDeath, this);
}

void CharacterBase::UpdateNone()
{
}

void CharacterBase::UpdateActive()
{
	//アニメーション処理
	Animation();
}

void CharacterBase::UpdateDeath()
{
}

void CharacterBase::Animation()
{
	//アニメーション状態をint化
	int state = static_cast<int>(animState_);

	//アニメーションの計算
	animCnt_ += animSpeed_;
	animNum_ = (int)animCnt_ % animMax_[state] + state * PLAYER_NUM_X;
}
