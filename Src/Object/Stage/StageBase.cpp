#include "StageBase.h"

StageBase::StageBase()
{
}

void StageBase::Load()
{
	//CSVデータ読み込み
	CsvDataLoad();
}

void StageBase::Init()
{
}

void StageBase::Update()
{
}

void StageBase::Draw()
{
}

void StageBase::Release()
{
}

void StageBase::CsvDataLoad()
{
    //ファイルの準備
    std::ifstream ifs = std::ifstream(groundCsvDate_);
    if (!ifs)
    {
        OutputDebugString(L"ステージのifstream準備失敗\n");
        return;
    }

    //二次元配列の場所を指定用
    int x = 0;
    int y = 0;

    std::string line;					//1行のデータを格納する領域
    while (getline(ifs, line))
    {
        //Split関数の戻り値受け取り用変数
        std::vector<std::string> strSplit; // 1行を1文字の動的配列に分割
        strSplit = Utility::Split(line, ',');

        int chipNo;

        //分割したデータをマップ配列に格納する
        for (int x = 0; x < strSplit.size(); x++)
        {
            chipNo = stoi(strSplit[x]);
            stageField_[fieldHeight_ + y][x] = chipNo;
        }
        y++;
    }
}
