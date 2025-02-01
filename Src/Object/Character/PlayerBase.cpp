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
	//âÊëúì«Ç›çûÇ›
	imgPlayer_ = ResourceManager::GetInstance().Load(
		ResourceManager::SRC::PLAYER_04).handleIds_;
}

void PlayerBase::UpdateNone()
{
}

void PlayerBase::UpdateActive()
{
	Animation();
}

void PlayerBase::UpdateDeath()
{
}

void PlayerBase::ProcessMove()
{
	auto& ins = InputManager::GetInstance();
	int stickX = ins.GetJPadInputState(pad_).AKeyRX;

	//âEà⁄ìÆ
	if (ins.IsNew(KEY_INPUT_RIGHT) || stickX > 0)
	{
		dir_ = false;
		animState_ = ANIM_STATE::RUN;
		Accele(MOVE_ACC);			//â¡ë¨
	}

	//ç∂à⁄ìÆ
	else if (ins.IsNew(KEY_INPUT_LEFT) || stickX < 0)
	{
		dir_ = true;
		animState_ = ANIM_STATE::RUN;
		Accele(-MOVE_ACC);			//â¡ë¨
	}
}
