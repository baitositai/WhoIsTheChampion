#include "../Application.h"
#include "../Utility/Utility.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/TextManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/Camera.h"
#include "TitleScene.h"

TitleScene::TitleScene(SceneManager& manager) :SceneBase(manager)
{
	//�e�평��������
	imgTitleLogo_ = -1;

	//�X�V�֐��̃Z�b�g
	updataFunc_ = [&](InputManager& input) {LoadingUpdate(input); };

	//�`��֐��̃Z�b�g
	drawFunc_ = std::bind(&TitleScene::LoadingDraw, this);
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Load(void)
{
	// �ǂݍ��ݎ��ԏ�����
	loadingTime_ = 0.0f;

	//�񓯊��ǂݍ��݂�true�ɂ���
	SetUseASyncLoadFlag(true);

	// �^�C�g�����S
	imgTitleLogo_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::TITLE_LOGO).handleId_;
	
	//�t�H���g
	loadFont_ = CreateFontToHandle(
		TextManager::GetInstance().GetFontName(TextManager::FONT_TYPE::HANAZOME).c_str(),
		LOAD_FONT_SIZE,
		0);
	mesFont_ = CreateFontToHandle(
		TextManager::GetInstance().GetFontName(TextManager::FONT_TYPE::HANAZOME).c_str(),
		MES_FONT_SIZE,
		0);
}

void TitleScene::Init(void)
{
	
}

void TitleScene::Update(InputManager& input)
{
	updataFunc_(input);
	return;
}

void TitleScene::Draw(void)
{
	drawFunc_();
	return;
}

void TitleScene::Release(void)
{
	DeleteFontToHandle(loadFont_);
}

void TitleScene::LoadingUpdate(InputManager& input)
{
	bool loadTimeOver = Utility::IsTimeOver(loadingTime_, LOADING_TIME);

	//���[�h���������������f
	if (GetASyncLoadNum() == 0 && loadTimeOver)
	{
		//�񓯊������𖳌��ɂ���
		SetUseASyncLoadFlag(false);

		//����������
		Init();

		//�t�F�[�h�C���J�n
		sceneManager_.StartFadeIn();

		//�X�V�֐��̃Z�b�g
		updataFunc_ = [&](InputManager& input) {NormalUpdate(input); };
		
		//�`��֐��̃Z�b�g
		drawFunc_ = std::bind(&TitleScene::NormalDraw, this);
	}
}

void TitleScene::NormalUpdate(InputManager& ins)
{
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
	}
}

void TitleScene::LoadingDraw(void)
{
	//�unow loading�v�̕`��
	DrawNowLoading();
}

void TitleScene::NormalDraw(void)
{
	//�w�i
	DrawBox(0, 0, Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, 0xffb6c1, true);

	// �`���O���t�B�b�N�̈�̎w��
	//sceneManager_.SetDrawingScreen(stageScreen_);

	//�����Ƀ��f���̕`��Ƃ�����(����)

	SetDrawScreen(sceneManager_.GetMainScreen());

	int cx = Application::SCREEN_HALF_X;
	int cy = Application::SCREEN_HALF_Y;

	// �^�C�g�����S
	DrawRotaGraph(
		cx, cy,
		0.5f, 0.0f, imgTitleLogo_, true);

	//�V�[���J��
	std::wstring mes = L"�X�y�[�X�������Ă�";
	DrawFormatStringToHandle(
		cx - mes.length() * MES_FONT_SIZE / 2,
		cy + 150,
		0xffffff,
		mesFont_,
		mes.c_str());
}
