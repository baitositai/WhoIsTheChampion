#include "PixelShader.h"

void PixelShader::Init()
{
	//�V�F�[�_�[�̓o�^
	InitPS();

	//�萔�o�b�t�@
	psConstBuf_ = CreateShaderConstantBuffer(sizeof(float) * 8);
}

void PixelShader::Destroy()
{
	//�V�F�[�_�[�̊J��
	for (auto& ps : psMap_)
	{
		DeleteShader(ps.second);
	}

	psMap_.clear();

	//�V�F�[�_�[�萔�o�b�t�@�̊J��
	DeleteShaderConstantBuffer(psConstBuf_);
}

void PixelShader::DrawGraph(const Vector2& pos, const int& handle)
{
	//�V�F�[�_�[�̐ݒ�
	int ps = SearchPS(PS_TYPE::TEXTURE);
	SetUsePixelShader(ps);

	//�V�F�[�_�[�Ƀe�N�X�`����]��
	SetUseTextureToShader(0, handle);

	//�T�C�Y
	int x, y;
	GetGraphSize(handle, &x, &y);

	//�`����W
	MakeSquereVertex(pos, { x,y });

	//�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
	DrawPolygonIndexed2DToShader(vertex_, NUM_VERTEX, index_, NUM_POLYGON);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void PixelShader::DrawExtendGraphToShader(const Vector2& pos, const Vector2& size, const int& handle)
{
	//�V�F�[�_�[�̐ݒ�
	int ps = SearchPS(PS_TYPE::TEXTURE);
	SetUsePixelShader(ps);

	//�V�F�[�_�[�Ƀe�N�X�`����]��
	SetUseTextureToShader(0, handle);

	//�`����W
	MakeSquereVertex(pos, size);

	//�o�C���j�A��ԃ��[�h
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	//�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
	DrawPolygonIndexed2DToShader(vertex_, NUM_VERTEX, index_, NUM_POLYGON);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�l�A���X�g�l�C�o�[�@
	SetDrawMode(DX_DRAWMODE_NEAREST);
}

void PixelShader::DrawExtendGraphToShader(const Vector2& pos, const Vector2& size, const int& handle, const PS_TYPE& type, const COLOR_F& buf, const COLOR_F& subBuf)
{
	//�V�F�[�_�[�̐ݒ�
	int ps = SearchPS(type);
	SetUsePixelShader(ps);

	//�V�F�[�_�[�Ƀe�N�X�`����]��
	if (handle != -1)SetUseTextureToShader(0, handle);

	//�V�F�[�_�[�p�̒萔�o�b�t�@
	auto& cBuf = psConstBuf_;

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̃A�h���X���擾
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	*cbBuf = buf;
	cbBuf++;
	*cbBuf = subBuf;

	//�`����W
	MakeSquereVertex(pos, size);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(cBuf);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^�ɃZ�b�g
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, CONSTANT_BUF_SLOT_BEGIN_PS);

	//�o�C���j�A��ԃ��[�h
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	//�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
	DrawPolygonIndexed2DToShader(vertex_, NUM_VERTEX, index_, NUM_POLYGON);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�l�A���X�g�l�C�o�[�@
	SetDrawMode(DX_DRAWMODE_NEAREST);
}

void PixelShader::MakeSquereVertex(Vector2 pos, Vector2 size)
{
	int cnt = 0;
	float sX = static_cast<float>(pos.x);
	float sY = static_cast<float>(pos.y);
	float eX = static_cast<float>(pos.x + size.x);
	float eY = static_cast<float>(pos.y + size.y);

	// �S���_�̏�����
	for (int i = 0; i < NUM_VERTEX; i++)
	{
		vertex_[i].rhw = 1.0f;
		vertex_[i].dif = GetColorU8(255, 255, 255, 255);
		vertex_[i].spc = GetColorU8(255, 255, 255, 255);
		vertex_[i].su = 0.0f;
		vertex_[i].sv = 0.0f;
	}

	// ����
	vertex_[cnt].pos = VGet(sX, sY, 0.0f);
	vertex_[cnt].u = 0.0f;
	vertex_[cnt].v = 0.0f;
	cnt++;

	// �E��
	vertex_[cnt].pos = VGet(eX, sY, 0.0f);
	vertex_[cnt].u = 1.0f;
	vertex_[cnt].v = 0.0f;
	cnt++;

	// �E��
	vertex_[cnt].pos = VGet(eX, eY, 0.0f);
	vertex_[cnt].u = 1.0f;
	vertex_[cnt].v = 1.0f;
	cnt++;

	// ����
	vertex_[cnt].pos = VGet(sX, eY, 0.0f);
	vertex_[cnt].u = 0.0f;
	vertex_[cnt].v = 1.0f;

	// ���_�C���f�b�N�X
	cnt = 0;
	index_[cnt++] = 0;
	index_[cnt++] = 1;
	index_[cnt++] = 3;

	index_[cnt++] = 1;
	index_[cnt++] = 2;
	index_[cnt++] = 3;
}

void PixelShader::InitPS()
{
	std::wstring path = L"Data/Shader/";
	std::wstring fileName;

	auto loadPS = [&](PS_TYPE type, std::wstring fName) 
	{
		fileName = path + fName;
		psMap_.emplace(std::make_pair(type, LoadPixelShader(fileName.c_str())));
	};

	loadPS(PS_TYPE::TEXTURE, L"Texture.cso");
	loadPS(PS_TYPE::FADE, L"Fade.cso");
	loadPS(PS_TYPE::FADE_TEXTURE, L"FadeTextrure.cso");
	//loadPS(PS_TYPE::COL_TX, L"ColorTex.cso");

	fileName = L"x64/Debug/ColorTex.cso";
	psMap_.emplace(std::make_pair(PS_TYPE::COL_TX, LoadPixelShader(fileName.c_str())));
}

const int& PixelShader::SearchPS(const PS_TYPE& ps) const
{
	//�o�^���s���Ă��邩���f
	const auto& psPair = psMap_.find(ps);
	if (psPair == psMap_.end())
	{
		//�o�^����Ă��Ȃ�
		//TRACE("�s�N�Z���V�F�[�_�[���o�^����Ă��܂���");
		return -1;
	}

	return psMap_.at(ps);
}

PixelShader::PixelShader()
{
	Init();
}
