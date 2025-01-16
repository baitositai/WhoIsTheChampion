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

	//�����摜������
	int value = -1;
	imgPlayer_ = &value;

	//�e��ύX�����̊i�[
	stateChanges_.emplace(STATE::NONE, std::bind(&CharacterBase::ChangeNone, this));
	stateChanges_.emplace(STATE::ACTIVE, std::bind(&CharacterBase::ChangeActive, this));
	stateChanges_.emplace(STATE::DEATH, std::bind(&CharacterBase::ChangeDeath, this));
}

void CharacterBase::Load()
{
	//�摜�ǂݍ���
	imgPlayer_ = ResourceManager::GetInstance().Load(
		ResourceManager::SRC::PLAYER_01).handleIds_;
}

void CharacterBase::Init()
{
#pragma region �X�e�[�^�X�ݒ�
	//�����ʒu
	pos_ = { FIRST_POS_X, FIRST_POS_Y };

	//�v���C���[�g�嗦
	rate_ = 1.0f;

	//�v���C���[��]
	angle_ = 0.0f;

	//�v���C���[�T�C�Y
	size_ = { SIZE_X, SIZE_Y };

	//����
	dir_ = false;

	//�ړ��X�s�[�h
	moveSpeed_ = MOVE_SPEED;
#pragma endregion 

#pragma region �A�j���[�V�����ݒ�
	//�A�j���[�V�����J�E���g
	animCnt_ = 0.0f;

	//�A�j���[�V�����ԍ�
	animNum_ = 0;

	//�A�j���[�V�����X�s�[�h
	animSpeed_ = ANIM_SPEED;

	//�A�j���[�V�����ő吔
	animMax_[static_cast<int>(ANIM_STATE::IDLE)] = ANIM_NUM_IDLE;
	animMax_[static_cast<int>(ANIM_STATE::RUN)] = ANIM_NUM_RUN;
	animMax_[static_cast<int>(ANIM_STATE::JUMP)] = ANIM_NUM_JUMP;
	animMax_[static_cast<int>(ANIM_STATE::DOUBLE_JUMP)] = ANIM_NUM_DOUBLE_JUMP;
	animMax_[static_cast<int>(ANIM_STATE::FALL)] = ANIM_NUM_FALL;
	animMax_[static_cast<int>(ANIM_STATE::HIT)] = ANIM_NUM_HIT;
	animMax_[static_cast<int>(ANIM_STATE::WALL_JUMP)] = ANIM_NUM_WALL_JUMP;
#pragma endregion 

	//�������
	ChangeState(STATE::ACTIVE);

	//�����A�j���[�V�������
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
	// ��Ԏ󂯎��
	state_ = state;

	// �e��ԑJ�ڂ̏�������
	stateChanges_[state_]();
}

inline void CharacterBase::ChangeAnimState(const ANIM_STATE state)
{
	//��Ԏ󂯎��
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
	//�A�j���[�V��������
	Animation();
}

void CharacterBase::UpdateDeath()
{
}

void CharacterBase::Animation()
{
	//�A�j���[�V������Ԃ�int��
	int state = static_cast<int>(animState_);

	//�A�j���[�V�����̌v�Z
	animCnt_ += animSpeed_;
	animNum_ = (int)animCnt_ % animMax_[state] + state * PLAYER_NUM_X;
}
