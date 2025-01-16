#pragma once
#include "../framework.h"
#include "../Utility/StaticSingleton.h"
#include "../Common/Fader.h"
#include "../Common/Vector2.h"
#include "Camera.h"

class SceneBase;
class InputManager;
class Fader;
class Camera;

class SceneManager : public StaticSingleton<SceneManager>
{

public:

	//FPS�l
	static constexpr float DEFAULT_FPS = 60.0f;

	//�d��
	static constexpr float GRAVITY = 9.81f;

	//�f���^�^�C��
	static constexpr float DELTA_TIME = 1.0f / 60.0f;

	// �V�[���Ǘ��p
	enum class SCENE_ID
	{
		NONE,
		TITLE,
		GAME
	};
	
	void Init(void);
	void Init3D(void);

	/// <summary>
	/// �擪�́iUpdata���Ă΂��j�V�[����؂�ւ���
	/// </summary>
	/// <param name="scene">�؂�ւ���̃V�[��</param>
	void CreateScene(std::shared_ptr<SceneBase> scene);

	/// <summary>
	/// ���ׂẴV�[����؂�ւ���
	/// </summary>
	/// <param name="scene">�؂�ւ���̃V�[��</param>
	void ChangeAllScene(std::shared_ptr<SceneBase> scene);

	/// <summary>
	/// �V�[�����v�b�V������B�X�^�b�N�̐���������
	/// ��ԏ�̃V�[����Updata�����Ă΂�܂���B
	/// </summary>
	/// <param name="scene">�ςރV�[��</param>
	void PushScene(std::shared_ptr<SceneBase> scene);

	/// <summary>
	/// �X�^�b�N�̓��̃V�[�����폜����B
	/// �������A�X�^�b�N��ɃV�[����������Ȃ��ꍇ�́A�폜���Ȃ��B
	/// </summary>
	void PopScene();

	void Update(InputManager& ins);
	void Draw(void);

	// ���\�[�X�̔j��
	void Destroy(void);

	// ��ԑJ��
	void ChangeScene(SCENE_ID nextId);

	// �V�[��ID�̎擾
	SCENE_ID GetSceneID(void);

	// �f���^�^�C���̎擾
	float GetDeltaTime(void) const;

	// �o�ߎ��Ԃ̎擾
	const float& GetTotalTime(void) const { return totalTime_; }

	// ���C���X�N���[���̎擾
	const int& GetMainScreen(void) const { return mainScreen_; }

	// �J�����̎擾
	Camera& GetCamera(void) const;

	//�t�F�[�h�C���J�n
	void StartFadeIn(void);

	//�t�F�[�h�J���[�̎w��
	void SetFadeColor(unsigned int color);

	//�`��X�N���[���̃Z�b�g
	void SetDrawingScreen(const int& screenID);

private:

	//�V���O���g��
	THIS_CLASS_IS_STATIC_SINGLETON(SceneManager);

	SCENE_ID sceneId_;
	SCENE_ID waitSceneId_;

	// �t�F�[�h
	std::unique_ptr<Fader> fader_;

	// �J����
	std::unique_ptr<Camera> camera_;

	// ���ݎ��s���̃V�[��
	std::list<std::shared_ptr<SceneBase>> scenes_;

	// �V�[���J�ڒ�����
	bool isSceneChanging_;

	// �f���^�^�C��
	std::chrono::system_clock::time_point preTime_;
	float deltaTime_;

	//�o�ߎ���
	float totalTime_;

	//���C���X�N���[��
	int mainScreen_;

	//�X�N���[�����W
	Vector2 screenPos_;

	//�X�N���[���U��
	float amplitude_;

	//�t���[��
	int frame_;
	
	// �f�t�H���g�R���X�g���N�^��private�ɂ��āA
	// �O�����琶���ł��Ȃ��l�ɂ���
	SceneManager(void);
	// �f�X�g���N�^�����l
	~SceneManager(void) = default;

	// �f���^�^�C�������Z�b�g����
	void ResetDeltaTime(void);

	// �V�[���J��
	void DoChangeScene(SCENE_ID sceneId);

	// �t�F�[�h
	void Fade(void);

};