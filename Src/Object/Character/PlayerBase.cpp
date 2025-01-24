#include "PlayerBase.h"
#include "../../Manager/ResourceManager.h"
#include "../../Manager/TextManager.h"
#include "../../Manager/InputManager.h"

PlayerBase::PlayerBase()
{
}

PlayerBase::~PlayerBase()
{
	
}

void PlayerBase::Load()
{
	//画像読み込み
	imgPlayer_ = ResourceManager::GetInstance().Load(
		ResourceManager::SRC::PLAYER_01).handleIds_;
}

void PlayerBase::UpdateNone()
{
}

void PlayerBase::UpdateActive()
{
	//移動操作処理
	ProcessMove();

	//ジャンプ操作処理
	ProcessJump();


	//アニメーション
	Animation();
}

void PlayerBase::UpdateDeath()
{
}

void PlayerBase::ProcessMove()
{
	auto& ins = InputManager::GetInstance();
	int stickX = ins.GetJPadInputState(pad_).AKeyRX;

	//右移動
	if (ins.IsNew(KEY_INPUT_RIGHT) || stickX > 0)
	{
		dir_ = false;
		animState_ = ANIM_STATE::RUN;
		Accele(MOVE_ACC);			//加速
	}

	//左移動
	else if (ins.IsNew(KEY_INPUT_LEFT) || stickX < 0)
	{
		dir_ = true;
		animState_ = ANIM_STATE::RUN;
		Accele(-MOVE_ACC);			//加速
	}
}

void PlayerBase::ProcessJump()
{
}
