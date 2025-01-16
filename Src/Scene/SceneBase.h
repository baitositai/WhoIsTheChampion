#pragma once
#include "../framework.h"
#include "../Application.h"

class SceneManager;
class InputManager;

//�ŒჍ�[�f�B���O����
constexpr float LOADING_TIME = 1.0f;

//�t�H���g�T�C�Y
constexpr int LOAD_FONT_SIZE = 28;

//���[�f�B���O
constexpr int COMMA_MAX_NUM = 5;			//�unow loading......�v�̃R���}�̐�
constexpr float COMMA_TIME = 0.3f;			//�unow loading......�v�̃R���}���𑝂₷����
constexpr int LOADING_STRING_POS_X = Application::SCREEN_SIZE_X - 200;	//�unow loading......�v�̍��WX
constexpr int LOADING_STRING_POS_Y = Application::SCREEN_SIZE_Y - LOAD_FONT_SIZE - 15;	//�unow loading......�v�̍��WY

class SceneBase
{

public:

	//�V�[���}�l�[�W���[
	SceneManager& sceneManager_;

	// �R���X�g���N�^
	SceneBase(SceneManager& scene);

	// �f�X�g���N�^
	virtual ~SceneBase(void) = 0;

	// �ǂݍ��ݏ���
	virtual void Load(void) = 0;

	// ����������
	virtual void Init(void) = 0;

	// �X�V�X�e�b�v
	virtual void Update(InputManager& input) = 0;

	// �`�揈��
	virtual void Draw(void) = 0;

	// �������
	virtual void Release(void) = 0;

protected:

	//���[�f�B���O���`��t�H���g
	int loadFont_;

	//���[�f�B���O�o�ߎ���
	float loadingTime_;

	std::function<void(InputManager&)> updataFunc_;
	std::function<void(void)> drawFunc_;
	
	//�unow loading......�v�̕`��
	void DrawNowLoading(void);

};
