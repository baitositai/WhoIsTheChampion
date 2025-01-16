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

	//�ǂݍ���
	void Load();

	//����������
	void Reset();
};

