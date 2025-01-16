#include <DxLib.h>
#include "../Application.h"
#include "../Shader/PixelShader.h"
#include "Fader.h"

Fader::STATE Fader::GetState(void) const
{
	return state_;
}

bool Fader::IsEnd(void) const
{
	return isEnd_;
}

void Fader::SetFade(STATE state)
{
	state_ = state;
	if (state_ != STATE::NONE)
	{
		isPreEnd_ = false;
		isEnd_ = false;
	}
}

void Fader::Init(void)
{
	state_ = STATE::NONE;
	alpha_ = 0;
	isPreEnd_ = true;
	isEnd_ = true;

	//�t�F�[�h�V�F�[�_�[�摜
	imgFade_ = LoadGraph(L"Data/Image/Fade/79.png");
}

void Fader::Update(void)
{

	if (isEnd_)
	{
		return;
	}

	switch (state_)
	{
	case STATE::NONE:
		return;

	case STATE::FADE_OUT:
		alpha_ += SPEED_ALPHA;
		if (alpha_ > 255)
		{
			// �t�F�[�h�I��
			alpha_ = 255;
			if (isPreEnd_)
			{
				// 1�t���[����(Draw��)�ɏI���Ƃ���
				isEnd_ = true;
			}
			isPreEnd_ = true;
		}

		break;

	case STATE::FADE_IN:
		alpha_ -= SPEED_ALPHA;
		if (alpha_ < 0)
		{
			// �t�F�[�h�I��
			alpha_ = 0;
			if (isPreEnd_)
			{
				// 1�t���[����(Draw��)�ɏI���Ƃ���
				isEnd_ = true;
			}
			isPreEnd_ = true;
		}
		break;

	default:
		return;
	}

}

void Fader::Draw(void)
{

	switch (state_)
	{
	case STATE::NONE:
		return;
	case STATE::FADE_OUT:
	case STATE::FADE_IN:
		/*SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)alpha_);
		DrawBox(
			0, 0,
			Application::SCREEN_SIZE_X,
			Application::SCREEN_SIZE_Y,
			0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);*/

		auto& ds = PixelShader::GetInstance();
		COLOR_F buf = COLOR_F{ alpha_ / 255 };
		ds.DrawExtendGraphToShader(
			{ 0,0 },
			{ Application::SCREEN_SIZE_X,Application::SCREEN_SIZE_Y },
			imgFade_,
			PixelShader::PS_TYPE::FADE,
			buf
		);
		break;
	}

}

void Fader::SetFadeColor(unsigned int color)
{
	fadeColor_ = color;
}