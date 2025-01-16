#pragma once
class StageBase
{
public:

	StageBase();
	~StageBase();

	void Init();
	void Update();
	void Draw();
	void Release();

private:

	//読み込み
	void Load();

	//初期化処理
	void Reset();
};

