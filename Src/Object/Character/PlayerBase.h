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
		NORMAL,			//�ʏ�
		DIFF_COLOR,		//�F�Ⴂ
		MAX
	};

	//�����ʒu
	static constexpr float FIRST_POS_X = Application::SCREEN_HALF_X;
	static constexpr float FIRST_POS_Y = Application::SCREEN_SIZE_Y - 300;

	//�v���C���[�T�C�Y
	static constexpr int SIZE_X = PLAYER_RUN_SIZE_X / PLAYER_RUN_NUM_X;
	static constexpr int SIZE_Y = PLAYER_RUN_SIZE_Y / PLAYER_RUN_NUM_Y;

	//�ړ����x
	static constexpr float MOVE_SPEED = 3.0f;

	//�A�j���[�V�����X�s�[�h
	static constexpr float ANIM_SPEED = 0.2f;

	//RUN�A�j���[�V������
	static constexpr int ANIM_RUN_NUM = PLAYER_RUN_NUM_X * PLAYER_RUN_NUM_Y;

	//�t�H���g�T�C�Y
	static constexpr int FONT_SIZE = 64;

	//��ލő��
	static constexpr int TYPE_MAX = static_cast<int>(DRAW_TYPE::MAX);

	PlayerBase();
	~PlayerBase();

	void Load();
	void Init();
	virtual void Update();
	virtual void Draw();
	void Release();

private:

	//�v���C���[�摜
	int *imgPlayer_;

	//�v���C���[�g�嗦
	float rate_;

	//�v���C���[��]
	float angle_;

	//���W
	Vector2F pos_;

	//�v���C���[�T�C�Y
	Vector2 size_;

	//����
	bool dir_;

	//�ړ��X�s�[�h
	float moveSpeed_;

	//�A�j���[�V�����J�E���g
	float animCnt_;

	//�A�j���[�V�����ԍ�
	int animNum_;

	//�A�j���[�V�����X�s�[�h
	float animSpeed_;

	//�`����
	DRAW_TYPE type_;

	//�t�H���g
	int font_;

	//���݂̎�ޖ�
	std::wstring name_;

	// ��ފǗ�(��ޑJ�ڎ���������)
	std::map<DRAW_TYPE, std::function<void(void)>> typeChanges_;

	// ��ފǗ�
	std::function<void(void)> typeDraw_;

	//�s�N�Z���V�F�[�_�[
	PixelShader& ps_;

	//��ԕύX
	void ChangeType(const DRAW_TYPE type);
	void ChangeTypeNormal();
	void ChangeTypeDiffColor();

	//��ޕʕ`��
	void NormalDraw();
	void DiffColorDraw();

	//��ޖ��̕`��
	void NameDraw();

	//�A�j���[�V��������
	void Animation();

	//�f�o�b�O�`��
	void DebagDraw();
	
};

