#pragma once
#include "SceneBase.h"
#include "../framework.h"

class TitleScene : public SceneBase
{

public:

	//�^�C�g���t�H���g�T�C�Y
	static constexpr int MES_FONT_SIZE = 28;

	// �R���X�g���N�^
	TitleScene(SceneManager& manager);

	// �f�X�g���N�^
	~TitleScene(void);

	void Load(void) override;
	void Init(void) override;
	void Update(InputManager& ins) override;
	void Draw(void) override;
	void Release(void) override;

private:	
	
	// �^�C�g�����S
	int imgTitleLogo_;

	// ���b�Z�[�W�t�H���g
	int mesFont_;

	// �X�V�֐�
	void LoadingUpdate(InputManager& ins);
	void NormalUpdate(InputManager& ins);

	// �`��֐�
	void LoadingDraw(void);
	void NormalDraw(void);
};