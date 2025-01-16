#include "../Manager/SceneManager.h"
#include "SceneBase.h"

SceneBase::SceneBase(SceneManager& scene) :sceneManager_(scene)
{
	loadingTime_ = 0.0f;
	loadFont_ = -1;
}
SceneBase::~SceneBase(void)
{
}

void SceneBase::DrawNowLoading(void)
{
	//���[�h��
	auto time = sceneManager_.GetTotalTime();
	int count = static_cast<int>(time / COMMA_TIME);
	count %= COMMA_MAX_NUM;

	std::wstring loadStr = L"Now loading";
	std::wstring dotStr = L".";

	for (int i = 0; i < count; i++)
	{
		loadStr += dotStr;
	}
	DrawStringToHandle(LOADING_STRING_POS_X, LOADING_STRING_POS_Y, loadStr.c_str(), 0xfff000, loadFont_);

}
