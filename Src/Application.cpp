#include "FpsControl/FpsControl.h"
#include "Manager/ResourceManager.h"
#include "Manager/TextManager.h"
#include "Manager/InputManager.h"
#include "Manager/SceneManager.h"
#include "Shader/PixelShader.h"
#include "Scene/TitleScene.h"
#include "Scene/GameScene.h"
#include "Application.h"

Application* Application::instance_ = nullptr;

const std::wstring Application::PATH_IMAGE = L"Data/Image/";
const std::wstring Application::PATH_MODEL = L"Data/Model/";
const std::wstring Application::PATH_EFFECT = L"Data/Effect/";
const std::wstring Application::PATH_FONT = L"Data/Font/";
const std::wstring Application::PATH_TEXT = L"Data/Text/";
const std::wstring Application::PATH_CSV = L"Data/CSV/";
const std::wstring Application::PATH_JSON = L"Data/JSON/";

void Application::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new Application();
	}
	instance_->Init();
}

Application& Application::GetInstance(void)
{
	return *instance_;
}

void Application::Init(void)
{

	// �A�v���P�[�V�����̏����ݒ�
	SetWindowText(L"�����������Ȃ��̖�Y");

	// �E�B���h�E�T�C�Y
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);
	ChangeWindowMode(true);

	// DxLib�̏�����
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	isInitFail_ = false;
	if (DxLib_Init() == -1)
	{
		isInitFail_ = true;
		return;
	}

	// �L�[���䏉����
	SetUseDirectInputFlag(true);

	// ���\�[�X�Ǘ�������
	ResourceManager::GetInstance();

	// �e�L�X�g�Ǘ�������
	TextManager::GetInstance();

	// FPS������
	fps_ = std::make_unique<FpsControl>();
	fps_->Init();
}

void Application::Run(void)
{
	auto& inputManager = InputManager::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();

	//�����V�[��
	sceneManager.CreateScene(std::make_shared<GameScene>(sceneManager));

	// �Q�[�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//�t���[�����[�g���X�V
		if (!fps_->UpdateFrameRate()) continue;

		//�e��X�V����
		inputManager.Update();
		sceneManager.Update(inputManager);

		//�`�揈��
		sceneManager.Draw();

		//�t���[�����[�g�v�Z
		fps_->CalcFrameRate();

		//�t���[�����[�g�`��(�f�o�b�O�p)
		//fps_->DrawFrameRate();

		ScreenFlip();
	}
}

void Application::Destroy(void)
{

	InputManager::GetInstance().Destroy();
	ResourceManager::GetInstance().Destroy();
	SceneManager::GetInstance().Destroy();
	TextManager::GetInstance().Destroy();
	PixelShader::GetInstance().Destroy();
	
	// DxLib�I��
	if (DxLib_End() == -1)
	{
		isReleaseFail_ = true;
	}

	delete instance_;

}

bool Application::IsInitFail(void) const
{
	return isInitFail_;
}

bool Application::IsReleaseFail(void) const
{
	return isReleaseFail_;
}

Application::Application(void)
{
	isInitFail_ = false;
	isReleaseFail_ = false;
	fps_ = nullptr;
}
