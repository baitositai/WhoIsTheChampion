#pragma once
#include "../../Application.h"
#include "../../Manager/ResourceManager.h"
#include "../../Common/Vector2.h"
#include "../../Common/Vector2F.h"

class CharacterBase
{
public:

	//�L�����N�^�[���
	enum class STATE
	{
		NONE,
		ACTIVE,
		DEATH,
	};

	//�A�j���[�V�������
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

	//�����ʒu
	static constexpr float FIRST_POS_X = Application::SCREEN_HALF_X;
	static constexpr float FIRST_POS_Y = Application::SCREEN_SIZE_Y - 300;

	//�v���C���[�T�C�Y
	static constexpr int SIZE_X = PLAYER_SIZE_X / PLAYER_NUM_X;
	static constexpr int SIZE_Y = PLAYER_SIZE_Y / PLAYER_NUM_Y;

	//�ړ����x
	static constexpr float MOVE_SPEED = 3.0f;

	//�e��A�j���[�V������
	static constexpr int ANIM_NUM_IDLE = 11;
	static constexpr int ANIM_NUM_RUN = 12;
	static constexpr int ANIM_NUM_JUMP = 1;
	static constexpr int ANIM_NUM_DOUBLE_JUMP = 6;
	static constexpr int ANIM_NUM_FALL = 1;
	static constexpr int ANIM_NUM_HIT = 7;
	static constexpr int ANIM_NUM_WALL_JUMP = 5;

	//�A�j���[�V�����X�s�[�h
	static constexpr float ANIM_SPEED = 0.3f;

	//�A�j���[�V������ސ�
	static constexpr int ANIM_STATE_MAX = static_cast<int>(ANIM_STATE::MAX);

	CharacterBase();
	~CharacterBase() = default;

	virtual void Load();
	virtual	void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Release();

	//��ԕύX
	void ChangeState(const STATE state);

	//�A�j���[�V�����̕ύX
	inline void ChangeAnimState(const ANIM_STATE state);

private:

	//���
	STATE state_;

	//�v���C���[�摜
	int* imgPlayer_;

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

	//�A�j���[�V�������
	ANIM_STATE animState_;

	//�A�j���[�V�����J�E���g
	float animCnt_;

	//�A�j���[�V�����ԍ�
	int animNum_;

	//�A�j���[�V�����ő吔
	int animMax_[ANIM_STATE_MAX];

	//�A�j���[�V�����X�s�[�h
	float animSpeed_;

	// ��ԊǗ�(��ԑJ�ڎ���������)
	std::map<STATE, std::function<void(void)>> stateChanges_;

	// ��ԊǗ�
	std::function<void(void)> stateUpdate_;

	//��ԕύX
	void ChangeNone();
	void ChangeActive();
	void ChangeDeath();

	//��ԕʍX�V����
	void UpdateNone();
	void UpdateActive();
	void UpdateDeath();

	//�A�j���[�V��������
	void Animation();
};

