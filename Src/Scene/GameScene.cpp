#include "GameScene.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/TextManager.h"
#include "../Utility/Utility.h"
#include "../Object/Character/PlayerBase.h"

GameScene::GameScene(SceneManager& manager) :SceneBase(manager)
{
	//�X�V�֐��̃Z�b�g
	updataFunc_ = [&](InputManager& input) {LoadingUpdate(input); };

	//�`��֐��̃Z�b�g
	drawFunc_ = std::bind(&GameScene::LoadingDraw, this);
}

GameScene::~GameScene(void)
{
}

void GameScene::Load(void)
{
	// �ǂݍ��ݎ��ԏ�����
	loadingTime_ = 0.0f;

	//�񓯊��ǂݍ��݂�true�ɂ���
	SetUseASyncLoadFlag(true);

	//�t�H���g
	loadFont_ = CreateFontToHandle(
		TextManager::GetInstance().GetFontName(TextManager::FONT_TYPE::HANAZOME).c_str(),
		LOAD_FONT_SIZE,
		0);

	//�v���C���[
	player_ = std::make_unique<PlayerBase>();
	player_->Load();
}

void GameScene::Init(void)
{
	//�v���C���[
	player_->Init();
}

void GameScene::Update(InputManager& input)
{
	updataFunc_(input);
	return;
}

void GameScene::Draw(void)
{
	drawFunc_();
	return;
}

void GameScene::Release(void)
{
	player_->Release();

	//�t�H���g�폜
	DeleteFontToHandle(loadFont_);
}

void GameScene::LoadingUpdate(InputManager& ins)
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
		drawFunc_ = std::bind(&GameScene::NormalDraw, this);
	}
}

void GameScene::NormalUpdate(InputManager& ins)
{
	//�v���C���[�X�V
	player_->Update();

	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().
			ChangeScene(SceneManager::SCENE_ID::TITLE);
	}
}

void GameScene::LoadingDraw(void)
{
	//�unow loading�v�̕`��
	DrawNowLoading();
}

void GameScene::NormalDraw(void)
{
	//�w�i
	DrawBox(0, 0, Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, 0xffb6c1, true);

	SetDrawScreen(sceneManager_.GetMainScreen());

	//�f�o�b�O�`��
	DebagDraw();

	//�v���C���[�`��
	player_->Draw();
}

void GameScene::DebagDraw()
{
}
