#include <DxLib.h>
#include "../Application.h"
#include "Resource.h"
#include "ResourceManager.h"

void ResourceManager::Init(void)
{
	Resource res;
	std::wstring path_omuretu = L"Omuretu/";

	//タイトルロゴ
	res = Resource(Resource::TYPE::IMG, Application::PATH_IMAGE + L"TitleLogo.png");
	resourcesMap_.emplace(SRC::TITLE_LOGO, res);

	//プレイヤー(走る)
	res = Resource(Resource::TYPE::IMGS, Application::PATH_IMAGE + path_omuretu + L"Run.png", 
		PLAYER_RUN_NUM_X, PLAYER_RUN_NUM_Y, PLAYER_RUN_SIZE_X, PLAYER_RUN_SIZE_Y);
	resourcesMap_.emplace(SRC::OMU_RUN, res);

	//テスト
	res = Resource(Resource::TYPE::IMG, Application::PATH_IMAGE + path_omuretu + L"Run.png");
	resourcesMap_.emplace(SRC::TEST, res);
}

void ResourceManager::Release(void)
{
	for (auto& p : loadedMap_)
	{
		p.second->Release();
		delete p.second;
	}

	loadedMap_.clear();
}

void ResourceManager::Destroy(void)
{
	Release();
	resourcesMap_.clear();
}

Resource ResourceManager::Load(SRC src)
{
	Resource* res = _Load(src);
	if (res == nullptr)
	{
		return Resource();
	}
	Resource ret = *res;
	return *res;
}

int ResourceManager::LoadModelDuplicate(SRC src)
{
	Resource* res = _Load(src);
	if (res == nullptr)
	{
		return -1;
	}

	int duId = MV1DuplicateModel(res->handleId_);
	res->duplicateModelIds_.push_back(duId);

	return duId;
}

ResourceManager::ResourceManager(void)
{
	Init();
}

Resource* ResourceManager::_Load(SRC src)
{
	const auto& lPair = loadedMap_.find(src);
	if (lPair != loadedMap_.end())
	{
		return lPair->second;
	}

	const auto& rPair = resourcesMap_.find(src);
	if (rPair == resourcesMap_.end())
	{
		// 登録されていない
		return nullptr;
	}

	rPair->second.Load();

	// 念のためコピーコンストラクタ
	Resource* ret = new Resource(rPair->second);
	loadedMap_.emplace(src, ret);

	return ret;
}
