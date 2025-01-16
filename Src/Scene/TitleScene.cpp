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
	//各種初期化処理
	imgTitleLogo_ = -1;

	//更新関数のセット
	updataFunc_ = [&](InputManager& input) {LoadingUpdate(input); };

	//描画関数のセット
	drawFunc_ = std::bind(&TitleScene::LoadingDraw, this);
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Load(void)
{
	// 読み込み時間初期化
	loadingTime_ = 0.0f;

	//非同期読み込みをtrueにする
	SetUseASyncLoadFlag(true);

	// タイトルロゴ
	imgTitleLogo_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::TITLE_LOGO).handleId_;
	
	//フォント
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

	//ロードが完了したか判断
	if (GetASyncLoadNum() == 0 && loadTimeOver)
	{
		//非同期処理を無効にする
		SetUseASyncLoadFlag(false);

		//初期化処理
		Init();

		//フェードイン開始
		sceneManager_.StartFadeIn();

		//更新関数のセット
		updataFunc_ = [&](InputManager& input) {NormalUpdate(input); };
		
		//描画関数のセット
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
	//「now loading」の描画
	DrawNowLoading();
}

void TitleScene::NormalDraw(void)
{
	//背景
	DrawBox(0, 0, Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, 0xffb6c1, true);

	// 描画先グラフィック領域の指定
	//sceneManager_.SetDrawingScreen(stageScreen_);

	//ここにモデルの描画とかする(多分)

	SetDrawScreen(sceneManager_.GetMainScreen());

	int cx = Application::SCREEN_HALF_X;
	int cy = Application::SCREEN_HALF_Y;

	// タイトルロゴ
	DrawRotaGraph(
		cx, cy,
		0.5f, 0.0f, imgTitleLogo_, true);

	//シーン遷移
	std::wstring mes = L"スペースを押してね";
	DrawFormatStringToHandle(
		cx - mes.length() * MES_FONT_SIZE / 2,
		cy + 150,
		0xffffff,
		mesFont_,
		mes.c_str());
}
