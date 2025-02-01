#pragma once
#include "../../framework.h"
#include "../../Utility/Utility.h"

class StageBase
{
public:

	StageBase();
	~StageBase() = default;

	void Load();
	void Init();
	void Update();
	void Draw();
	void Release();

private:

	//CSVÉfÅ[É^ì«Ç›çûÇ›
	void CsvDataLoad();

};

