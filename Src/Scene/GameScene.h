#pragma once
#include "../framework.h"
#include "SceneBase.h"

class PlayerBase;
class CharacterBase;
class StageBase;

class GameScene : public SceneBase
{
public:

	// �R���X�g���N�^
	GameScene(SceneManager& manager);

	// �f�X�g���N�^
	~GameScene(void);

	void Load(void) override;
	void Init(void) override;
	void Update(InputManager& input) override;
	void Draw(void) override;
	void Release(void) override;

private:	
	
	// �v���C���[(�L�����N�^�[)
	std::unique_ptr<PlayerBase> player_;

	//�X�e�[�W
	std::unique_ptr<StageBase> stage_;

	//Update�֐�
	void LoadingUpdate(InputManager& ins);
	void NormalUpdate(InputManager& ins);

	//�`��֐� 
	void LoadingDraw(void);
	void NormalDraw(void);

	//�f�o�b�O�`��
	void DebagDraw();
};

