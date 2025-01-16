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

	//“Ç‚İ‚İ
	void Load();

	//‰Šú‰»ˆ—
	void Reset();
};

