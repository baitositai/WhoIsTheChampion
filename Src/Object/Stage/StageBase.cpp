#include "StageBase.h"

StageBase::StageBase()
{
}

void StageBase::Load()
{
	//CSV�f�[�^�ǂݍ���
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
    //�t�@�C���̏���
    std::ifstream ifs = std::ifstream(groundCsvDate_);
    if (!ifs)
    {
        OutputDebugString(L"�X�e�[�W��ifstream�������s\n");
        return;
    }

    //�񎟌��z��̏ꏊ���w��p
    int x = 0;
    int y = 0;

    std::string line;					//1�s�̃f�[�^���i�[����̈�
    while (getline(ifs, line))
    {
        //Split�֐��̖߂�l�󂯎��p�ϐ�
        std::vector<std::string> strSplit; // 1�s��1�����̓��I�z��ɕ���
        strSplit = Utility::Split(line, ',');

        int chipNo;

        //���������f�[�^���}�b�v�z��Ɋi�[����
        for (int x = 0; x < strSplit.size(); x++)
        {
            chipNo = stoi(strSplit[x]);
            stageField_[fieldHeight_ + y][x] = chipNo;
        }
        y++;
    }
}
