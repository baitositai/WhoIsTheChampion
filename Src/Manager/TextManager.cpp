#include "../Application.h"
#include "TextManager.h"

void TextManager::Init()
{
    //�e�L�X�g�Ǘ�
    std::wstring text = (Application::PATH_TEXT + L"textData.txt").c_str();
    textDatas_ = LoadDialogues(text);

    //�t�H���g�֌W������
    InitFont();
}

void TextManager::Release()
{
    // �t�H���g�o�^����
    for (int i = 0; i < static_cast<int>(FONT_TYPE::MAX); i++)
    {
        if (RemoveFontResourceEx(
            (Application::PATH_FONT + fontPath_[i]).c_str(),
            FR_PRIVATE,
            NULL)
            == -1)
        {
            return;
        }
    }
}

std::wstring TextManager::TextLoad(TEXTS text)
{
    std::wstring* txt = _Load(text);
    if (txt == nullptr)
    {
        return L"null";
    }
    std::wstring ret = *txt;
    return ret;
}

int TextManager::GetTextSize(std::wstring txt,int num) const
{
    int ret = -1;

    // ���C�h�����p�̃o�b�t�@�T�C�Y���v�Z
    size_t bufferSize = std::swprintf(nullptr, 0, txt.c_str(), num) + 1; // +1�͏I�[�̃k�������p

    // ���C�h�����p�̃o�b�t�@���m��
    wchar_t* buffer = new wchar_t[bufferSize];

    // �o�b�t�@�Ƀt�H�[�}�b�g���ꂽ���������������
    std::swprintf(buffer, bufferSize, txt.c_str(), num);

    // �o�b�t�@���g���ĉ����������s���i���ɕ�����̃T�C�Y��Ԃ������j
    ret = std::wcslen(buffer);  // wchar_t �z��̒������擾

    delete[] buffer;  // ���I�����������
    return ret;
}

void TextManager::Destroy()
{
    Release();
}

void TextManager::InitFont()
{
    //�t�H���g�p�X�ݒ�
    fontPath_[static_cast<int>(FONT_TYPE::NORMAR)] = L"msgothic.ttc";
    fontPath_[static_cast<int>(FONT_TYPE::DOT)] = L"FontDot.otf";
    fontPath_[static_cast<int>(FONT_TYPE::LOGO)] = L"Corporate-Logo-Bold-ver3.otf";
    fontPath_[static_cast<int>(FONT_TYPE::BOKUTACHI)] = L"bokutachi.otf";
    fontPath_[static_cast<int>(FONT_TYPE::HANAZOME)] = L"PENGS.ttf";
    fontPath_[static_cast<int>(FONT_TYPE::BANANA)] = L"YDWbananaslipplus.otf";
    fontPath_[static_cast<int>(FONT_TYPE::PENGS)] = L"PENGS.ttf";

    //�t�H���g���O�ݒ�
    fontName_[static_cast<int>(FONT_TYPE::NORMAR)] = L"�l�r �S�V�b�N";
    fontName_[static_cast<int>(FONT_TYPE::DOT)] = L"�x�X�g�e��DOT";
    fontName_[static_cast<int>(FONT_TYPE::LOGO)] = L"�R�[�|���[�g�E���S ver3 Bold";
    fontName_[static_cast<int>(FONT_TYPE::BOKUTACHI)] = L"�ڂ������̃S�V�b�N";
    fontName_[static_cast<int>(FONT_TYPE::HANAZOME)] = L"�͂Ȃ��߃t�H���g";
    fontName_[static_cast<int>(FONT_TYPE::BANANA)] = L"�x�c�v �o�i�i�X���b�v plus plus";
    fontName_[static_cast<int>(FONT_TYPE::PENGS)] = L"PENGS";

    // �t�H���g���V�X�e���ɓo�^
    for (int i = 0; i < static_cast<int>(FONT_TYPE::MAX); i++)
    {
        if (AddFontResourceEx(
            (Application::PATH_FONT + fontPath_[i]).c_str(),
            FR_PRIVATE,
            NULL)
            == -1)
        {
            return;
        }
    }
}

std::unordered_map<TextManager::TEXTS, std::wstring>
TextManager::LoadDialogues(const std::wstring& filename)
{
    std::unordered_map<TEXTS, std::wstring> dialogues;
    std::wifstream file(filename);
    std::wstring line;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            size_t separatorPos = line.find(L":");
            if (separatorPos != std::wstring::npos) 
            {
                int id = std::stoi(line.substr(0, separatorPos));
                std::wstring dialogue = line.substr(separatorPos + 1);

                // id��񋓌^�ɃL���X�g���ă}�b�v�ɒǉ�
                dialogues[static_cast<TEXTS>(id)] = dialogue;
            }
        }
        file.close();
    }
    else 
    {
        std::cerr << "�t�@�C�����J���܂���ł����B" << std::endl;
    }

    return dialogues;
}

std::wstring* TextManager::_Load(TEXTS text)
{
    std::wstring* ret = new std::wstring;
    if (textDatas_.find(text) != textDatas_.end())
    {
        *ret = textDatas_.at(text);
        return ret;
    }

    *ret = L"�Z���t��������܂���B";

    return ret;
}

TextManager::TextManager(void)
{
    Init();
}
