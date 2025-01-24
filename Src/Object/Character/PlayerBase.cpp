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
	//�摜�ǂݍ���
	imgPlayer_ = ResourceManager::GetInstance().Load(
		ResourceManager::SRC::PLAYER_01).handleIds_;
}

void PlayerBase::UpdateNone()
{
}

void PlayerBase::UpdateActive()
{
	//�ړ����쏈��
	ProcessMove();

	//�W�����v���쏈��
	ProcessJump();


	//�A�j���[�V����
	Animation();
}

void PlayerBase::UpdateDeath()
{
}

void PlayerBase::ProcessMove()
{
	auto& ins = InputManager::GetInstance();
	int stickX = ins.GetJPadInputState(pad_).AKeyRX;

	//�E�ړ�
	if (ins.IsNew(KEY_INPUT_RIGHT) || stickX > 0)
	{
		dir_ = false;
		animState_ = ANIM_STATE::RUN;
		Accele(MOVE_ACC);			//����
	}

	//���ړ�
	else if (ins.IsNew(KEY_INPUT_LEFT) || stickX < 0)
	{
		dir_ = true;
		animState_ = ANIM_STATE::RUN;
		Accele(-MOVE_ACC);			//����
	}
}

void PlayerBase::ProcessJump()
{
}
