#include "PlayerBase.h"
#include "../../Manager/ResourceManager.h"
#include "../../Manager/TextManager.h"
#include "../../Manager/InputManager.h"

PlayerBase::PlayerBase()
	: ps_(PixelShader::GetInstance())
{
	angle_ = -1.0f;
	animCnt_ = -1.0f;
	animNum_ = -1;
	animSpeed_ = -1.0f;
	dir_ = false;
	font_ = -1;
	name_ = L"";
	moveSpeed_ = -1.0f;
	rate_ = -1.0f;

	//�����摜������
	int value = -1;
	imgPlayer_ = &value;

	//�e��ύX�����̊i�[
	typeChanges_.emplace(DRAW_TYPE::NORMAL, std::bind(&PlayerBase::ChangeTypeNormal, this));
	typeChanges_.emplace(DRAW_TYPE::DIFF_COLOR, std::bind(&PlayerBase::ChangeTypeDiffColor, this));
}

PlayerBase::~PlayerBase()
{
}

void PlayerBase::Load()
{
	//�v���C���[�摜
	imgPlayer_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::OMU_RUN).handleIds_;

	//�t�H���g�ǂݍ���
	font_ = CreateFontToHandle(
		TextManager::GetInstance().GetFontName(TextManager::FONT_TYPE::HANAZOME).c_str(),
		FONT_SIZE,
		0);
}

void PlayerBase::Init()
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
#pragma endregion 

	//��ނ̏�����
	ChangeType(DRAW_TYPE::NORMAL);

}

void PlayerBase::Update()
{
	//�A�j���[�V��������
	Animation();

	//��ނ̕ύX
	auto& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_RETURN))
	{
		//��ނ�ς���
		int type = static_cast<int>(type_);
		type++;
		if (type == TYPE_MAX) { type = 0; }	//�ő�̏ꍇ�ŏ��ɖ߂�
		type_ = static_cast<DRAW_TYPE>(type);
		ChangeType(type_);
	}
}

void PlayerBase::Draw()
{
	//��ޕʕ`��
	typeDraw_();

	//��ޖ��̕`��
	NameDraw();

	//�f�o�b�O�`��
	//DebagDraw();
}

void PlayerBase::Release()
{
	DeleteFontToHandle(font_);
}

void PlayerBase::ChangeType(const DRAW_TYPE type)
{
	// ��Ԏ󂯎��
	type_ = type;

	// �e��ԑJ�ڂ̏�������
	typeChanges_[type_]();
}

void PlayerBase::ChangeTypeNormal()
{
	typeDraw_ = std::bind(&PlayerBase::NormalDraw, this);
}

void PlayerBase::ChangeTypeDiffColor()
{
	typeDraw_ = std::bind(&PlayerBase::DiffColorDraw, this);
}

#pragma region typeDraw_�Ɋ܂܂��Draw�֐�

void PlayerBase::NormalDraw()
{
	name_ = L"�ʏ�";

	//�v���C���[
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

void PlayerBase::DiffColorDraw()
{
	name_ = L"�F�Ⴂ";
	//ps_.DrawGraph(pos_.ToVector2(), imgPlayer_[animNum_]);

	auto& ds = PixelShader::GetInstance();
	COLOR_F buf;
	buf.r = 1.0f;
	buf.g = 1.0f;
	buf.b = 1.0f;
	buf.a = 1.0f;
	COLOR_F subBuf;
	subBuf.r = OMU_RUN_NUM_X;
	subBuf.g = OMU_RUN_NUM_Y;
	subBuf.b = animNum_;
	subBuf.a = 1.0f;

	Vector2 pos = pos_.ToVector2();
	pos.x -= SIZE_X *6/ 2;
	pos.y -= SIZE_Y / 2;

	ds.DrawExtendGraphToShader(
		{ pos.x ,pos.y },
		{ SIZE_X *6,SIZE_Y },
		imgPlayer_[animNum_],
		PixelShader::PS_TYPE::COL_TX,
		buf,
		subBuf
	);
}

#pragma endregion


void PlayerBase::NameDraw()
{
	DrawBox(
		0, 0,
		FONT_SIZE * name_.length(),
		FONT_SIZE,
		0xff0000,
		true
	);

	DrawFormatStringToHandle(
		0, 0,
		0xffffff,
		font_,
		name_.c_str()
	);
}

void PlayerBase::Animation()
{
	animCnt_ += animSpeed_;
	animNum_ = (int)animCnt_ % ANIM_RUN_NUM;
}

void PlayerBase::DebagDraw()
{
}
