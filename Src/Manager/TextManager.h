#pragma once
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "../Utility/StaticSingleton.h"

class TextManager :
	public StaticSingleton<TextManager>
{
public:

	//���t�H���g�����͊ecpp�ōs���Ă�������
	//�@���̍�DeleteFontToHandle��Y�ꂸ�ɁI

	//�t�H���g���
	enum class FONT_TYPE
	{
		NORMAR,
		DOT,
		LOGO,
		BOKUTACHI,
		HANAZOME,
		BANANA,
		PENGS,
		MAX
	};

	//�e�L�X�g�Ăяo���p
	enum class TEXTS		//MES---���b�Z�[�W�̗�
	{
		LEVEL_UP,			//�����֌W�̃e�L�X�g
		LV_UP_SELECT_MES,
		LV_ATK_MES,
		LV_DEF_MES,
		LV_SPEED_MES,
		LV_LIFE_MES,
		MAX
	};

	//�e�L�X�g���������p(�e�L�X�g�̒��� �� �萔)
	static constexpr int CENTER_TEXT = 2;
	static constexpr int CENTER_TEXT_H = 4;	//�p���Ȃǂ̔��p�݂̂̃e�L�X�g�͂���Ŋ���

	void Init();
	void Release();

	//�e�L�X�g�ǂݍ���
	std::wstring TextLoad(TEXTS text);

	//�t�H���g���O�󂯎��
	inline std::wstring GetFontName(FONT_TYPE type) const { return fontName_[static_cast<int>(type)]; }

	//�e�L�X�g�T�C�Y�̎󂯎��
	int GetTextSize(std::wstring txt, int num)const;

	//�������
	void Destroy();

private:

	//�V���O���g���̐���
	THIS_CLASS_IS_STATIC_SINGLETON(TextManager);

	//�t�H���g���
	std::wstring fontPath_[static_cast<int>(FONT_TYPE::MAX)];	//�p�X
	std::wstring fontName_[static_cast<int>(FONT_TYPE::MAX)];	//���O

	//�f�[�^
	std::unordered_map<TextManager::TEXTS, std::wstring> textDatas_;

	//�t�H���g������
	void InitFont();

	//�e�L�X�g��ێ�����}�b�v
	std::unordered_map<TEXTS, std::wstring> LoadDialogues(const std::wstring& filename);

	//�e�L�X�g�̓ǂݍ���
	std::wstring* _Load(TEXTS text);

	// �f�t�H���g�R���X�g���N�^��private�ɂ��āA
	// �O�����琶���ł��Ȃ��l�ɂ���
	TextManager(void);
	~TextManager(void) = default;

};
