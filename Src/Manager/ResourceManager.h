#pragma once
#include "../framework.h"
#include "../Utility/StaticSingleton.h"
#include "Resource.h"

// �I�����c����摜
constexpr int OMU_RUN_NUM_X = 6;
constexpr int OMU_RUN_NUM_Y = 1;
constexpr int OMU_RUN_SIZE_X = 1080 / OMU_RUN_NUM_X;
constexpr int OMU_RUN_SIZE_Y = 240 / OMU_RUN_NUM_Y;

//�v���C���[�摜
constexpr int PLAYER_NUM_X = 12;
constexpr int PLAYER_NUM_Y = 7;
constexpr int PLAYER_SIZE_X = 600 / PLAYER_NUM_X;
constexpr int PLAYER_SIZE_Y = 350 / PLAYER_NUM_Y;

class ResourceManager :
	public StaticSingleton<ResourceManager>
{

public:

	// ���\�[�X��
	enum class SRC
	{
		TITLE_LOGO,
		OMU_RUN,
		PLAYER_01,
		PLAYER_02,
		PLAYER_03,
		PLAYER_04,
	};

	// ������
	void Init(void);

	// ���(�V�[���ؑ֎��Ɉ�U���)
	void Release(void);

	// ���\�[�X�̊��S�j��
	void Destroy(void);

	// ���\�[�X�̃��[�h
	Resource Load(SRC src);

	// ���\�[�X�̕������[�h(���f���p)
	int LoadModelDuplicate(SRC src);

private:

	//�V���O���g���̐���
	THIS_CLASS_IS_STATIC_SINGLETON(ResourceManager);

	// ���\�[�X�Ǘ��̑Ώ�
	std::map<SRC, Resource> resourcesMap_;

	// �ǂݍ��ݍς݃��\�[�X
	std::map<SRC, Resource*> loadedMap_;

	// �f�t�H���g�R���X�g���N�^��private�ɂ��āA
	// �O�����琶���ł��Ȃ��l�ɂ���
	ResourceManager(void);

	// �f�X�g���N�^�����l
	~ResourceManager(void) = default;

	// �������[�h
	Resource* _Load(SRC src);

};

