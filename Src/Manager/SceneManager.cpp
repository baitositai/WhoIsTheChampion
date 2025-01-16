#include "../framework.h"
#include "../Application.h"
#include "../Common/Fader.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "../Scene/TitleScene.h"
#include "../Scene/GameScene.h"
#include "InputManager.h"
#include "SceneManager.h"

void SceneManager::Init(void)
{

	sceneId_ = SCENE_ID::TITLE;
	waitSceneId_ = SCENE_ID::NONE;

	fader_ = std::make_unique<Fader>();
	fader_->Init();

	camera_ = std::make_unique<Camera>();
	camera_->Init();

	isSceneChanging_ = false;

	// �f���^�^�C��
	preTime_ = std::chrono::system_clock::now();

	//���C���X�N���[���̍쐬
	mainScreen_ = MakeScreen(Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, true);
	
	//�X�N���[�����W
	screenPos_ = { 0,0};

	// 3D�p�̐ݒ�
	Init3D();

	//// �����V�[���̐ݒ�
	//DoChangeScene(SCENE_ID::TITLE);

}

void SceneManager::Init3D(void)
{

	// �w�i�F�ݒ�
	SetBackgroundColor(0, 0, 0);

	// Z�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(true);

	// Z�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(true);

	// �o�b�N�J�����O��L���ɂ���
	SetUseBackCulling(true);

	// ���C�g�̐ݒ�
	SetUseLighting(true);

	// ���ʂ���΂߉��Ɍ����������C�g
	ChangeLightTypeDir({ 0.00f, -1.00f, 1.00f });

}

void SceneManager::CreateScene(std::shared_ptr<SceneBase> scene)
{
	if (scenes_.empty())
	{
		scenes_.push_back(scene);
	}
	else
	{
		scenes_.front() = scene;
	}

	//�f�[�^�̃��[�h
	scenes_.front()->Load();
}

void SceneManager::ChangeAllScene(std::shared_ptr<SceneBase> scene)
{
	//�t�F�[�h�J�n
	StartFadeIn();

	scenes_.clear();
	scenes_.push_back(scene);
	//�f�[�^�̃��[�h
	scenes_.front()->Load();
}

void SceneManager::PushScene(std::shared_ptr<SceneBase> scene)
{
	scene->Init();
	scenes_.push_front(scene);
}

void SceneManager::PopScene()
{
	if (scenes_.size() >= 1)
	{
		scenes_.pop_front();
	}
}

void SceneManager::Update(InputManager& ins)
{
	if (scenes_.empty())return;

	// �f���^�^�C��
	auto nowTime = std::chrono::system_clock::now();
	deltaTime_ = static_cast<float>(
		std::chrono::duration_cast<std::chrono::nanoseconds>(nowTime - preTime_).count() / 1000000000.0);
	preTime_ = nowTime;
	totalTime_ += GetDeltaTime();
	
	// �J�����X�V
	camera_->Update();
	
	//�t�F�[�h�X�V
	Fade();
	
	//�V�[���X�V
	scenes_.front()->Update(ins);

}

void SceneManager::Draw(void)
{
	// �`���O���t�B�b�N�̈�̎w��
	SetDrawingScreen(mainScreen_);

	//�V�[���`��(�Ō������`��)
	auto rit = scenes_.rbegin();
	for (; rit != scenes_.rend(); rit++)
	{
		(*rit)->Draw();
	}

	//�}�E�X�`��
	//auto& ins = InputManager::GetInstance();
	//Vector2 m = ins.GetMousePos();
	////DrawGraph(m.x, m.y, mouseImg_, true);
	//DrawCircle(m.x, m.y, 3, 0xff0000, true);


	// �Ó]�E���]
	fader_->Draw();

	// �`���O���t�B�b�N�̈�̎w��
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();
	DrawGraph(static_cast<int>(screenPos_.x), static_cast<int>(screenPos_.y), mainScreen_, true);

}

void SceneManager::Destroy(void)
{

	scenes_.front()->Release();

	camera_->Release();

}

void SceneManager::ChangeScene(SCENE_ID nextId)
{
	//�t�F�[�h���͎��s���Ȃ�
	if (!fader_->IsEnd())return;

	DeleteLightHandleAll();

	// �t�F�[�h�������I����Ă���V�[����ς���ꍇ�����邽�߁A
	// �J�ڐ�V�[���������o�ϐ��ɕێ�
	waitSceneId_ = nextId;

	// �t�F�[�h�A�E�g(�Ó])���J�n����
	fader_->SetFade(Fader::STATE::FADE_OUT);
	isSceneChanging_ = true;
}

SceneManager::SCENE_ID SceneManager::GetSceneID(void)
{
	return sceneId_;
}

float SceneManager::GetDeltaTime(void) const
{
	//return 1.0f / 60.0f;
	return deltaTime_;
}

Camera& SceneManager::GetCamera(void) const
{
	return *camera_;
}

void SceneManager::StartFadeIn(void)
{
	// �t�F�[�h�C�����J�n����
	fader_->SetFade(Fader::STATE::FADE_IN);
}

void SceneManager::SetFadeColor(unsigned int color)
{
	fader_->SetFadeColor(color);
}

void SceneManager::SetDrawingScreen(const int& screenID)
{
	SetDrawScreen(screenID);
	ClearDrawScreen();

	//�J�����ݒ�
	camera_->SetBeforeDraw();
}

SceneManager::SceneManager(void)
{
	sceneId_ = SCENE_ID::NONE;
	waitSceneId_ = SCENE_ID::NONE;

	scenes_.clear();

	isSceneChanging_ = false;

	// �f���^�^�C��
	deltaTime_ = DELTA_TIME;

	Init();
	
}

void SceneManager::ResetDeltaTime(void)
{
	deltaTime_ = 0.016f;
	preTime_ = std::chrono::system_clock::now();
}

void SceneManager::DoChangeScene(SCENE_ID sceneId)
{

	//// ���\�[�X�̉��
	//ResourceManager::GetInstance().Release();

	// �V�[����ύX����
	sceneId_ = sceneId;

	switch (sceneId_)
	{
	case SCENE_ID::TITLE:
		ChangeAllScene(std::make_shared<TitleScene>(*this));
		break;
	case SCENE_ID::GAME:
		ChangeAllScene(std::make_shared<GameScene>(*this));
		break;
	}

	ResetDeltaTime();

	waitSceneId_ = SCENE_ID::NONE;

}

void SceneManager::Fade(void)
{
	fader_->Update();

	Fader::STATE fState = fader_->GetState();
	switch (fState)
	{
	case Fader::STATE::FADE_IN:
		// ���]��
		if (fader_->IsEnd())
		{
			// ���]���I��������A�t�F�[�h�����I��
			fader_->SetFade(Fader::STATE::NONE);
			isSceneChanging_ = false;
		}
		break;
	case Fader::STATE::FADE_OUT:
		// �Ó]��
		if (fader_->IsEnd())
		{
			// ���S�ɈÓ]���Ă���V�[���J��
			DoChangeScene(waitSceneId_);
			// �Ó]���疾�]��
			fader_->SetFade(Fader::STATE::FADE_IN);
		}
		break;
	}
}