#include "../Application.h"
#include "TextManager.h"

void TextManager::Init()
{
    //テキスト管理
    std::wstring text = (Application::PATH_TEXT + L"textData.txt").c_str();
    textDatas_ = LoadDialogues(text);

    //フォント関係初期化
    InitFont();
}

void TextManager::Release()
{
    // フォント登録解除
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

    // ワイド文字用のバッファサイズを計算
    size_t bufferSize = std::swprintf(nullptr, 0, txt.c_str(), num) + 1; // +1は終端のヌル文字用

    // ワイド文字用のバッファを確保
    wchar_t* buffer = new wchar_t[bufferSize];

    // バッファにフォーマットされた文字列を書き込む
    std::swprintf(buffer, bufferSize, txt.c_str(), num);

    // バッファを使って何か処理を行う（仮に文字列のサイズを返す処理）
    ret = std::wcslen(buffer);  // wchar_t 配列の長さを取得

    delete[] buffer;  // 動的メモリを解放
    return ret;
}

void TextManager::Destroy()
{
    Release();
}

void TextManager::InitFont()
{
    //フォントパス設定
    fontPath_[static_cast<int>(FONT_TYPE::NORMAR)] = L"msgothic.ttc";
    fontPath_[static_cast<int>(FONT_TYPE::DOT)] = L"FontDot.otf";
    fontPath_[static_cast<int>(FONT_TYPE::LOGO)] = L"Corporate-Logo-Bold-ver3.otf";
    fontPath_[static_cast<int>(FONT_TYPE::BOKUTACHI)] = L"bokutachi.otf";
    fontPath_[static_cast<int>(FONT_TYPE::HANAZOME)] = L"PENGS.ttf";
    fontPath_[static_cast<int>(FONT_TYPE::BANANA)] = L"YDWbananaslipplus.otf";
    fontPath_[static_cast<int>(FONT_TYPE::PENGS)] = L"PENGS.ttf";

    //フォント名前設定
    fontName_[static_cast<int>(FONT_TYPE::NORMAR)] = L"ＭＳ ゴシック";
    fontName_[static_cast<int>(FONT_TYPE::DOT)] = L"ベストテンDOT";
    fontName_[static_cast<int>(FONT_TYPE::LOGO)] = L"コーポレート・ロゴ ver3 Bold";
    fontName_[static_cast<int>(FONT_TYPE::BOKUTACHI)] = L"ぼくたちのゴシック";
    fontName_[static_cast<int>(FONT_TYPE::HANAZOME)] = L"はなぞめフォント";
    fontName_[static_cast<int>(FONT_TYPE::BANANA)] = L"ＹＤＷ バナナスリップ plus plus";
    fontName_[static_cast<int>(FONT_TYPE::PENGS)] = L"PENGS";

    // フォントをシステムに登録
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

                // idを列挙型にキャストしてマップに追加
                dialogues[static_cast<TEXTS>(id)] = dialogue;
            }
        }
        file.close();
    }
    else 
    {
        std::cerr << "ファイルを開けませんでした。" << std::endl;
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

    *ret = L"セリフが見つかりません。";

    return ret;
}

TextManager::TextManager(void)
{
    Init();
}
