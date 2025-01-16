#pragma once
#include "../framework.h"
#include "../Utility/StaticSingleton.h"
#include "../Common/Vector2.h"

class PixelShader
	: public StaticSingleton<PixelShader>
{
public:

	// �s�N�Z���V�F�[�_�p�I���W�i���萔�o�b�t�@�̎g�p�J�n�X���b�g
	static constexpr int CONSTANT_BUF_SLOT_BEGIN_PS = 3;
	
	// ���_��
	static constexpr int NUM_VERTEX = 4;
	
	// ���_�C���f�b�N�X��
	static constexpr int NUM_VERTEX_IDX = 6;
	
	// �|���S����
	static constexpr int NUM_POLYGON = 2;

	enum class PS_TYPE
	{
		TEXTURE,
		COL_TX,
		FADE,
		FADE_TEXTURE,
		MAX
	};

	//����������
	void Init();

	//�������
	void Destroy();

	//�摜�ʏ�`��
	void DrawGraph(
		const Vector2& pos, 
		const int& handle);

	//�T�C�Y�w��`��i�ʏ�j
	void DrawExtendGraphToShader(
		const Vector2& pos,
		const Vector2& size, 
		const int& handle);

	//�T�C�Y�w��`��
	void DrawExtendGraphToShader(
		const Vector2& pos, 
		const Vector2& size,
		const int& handle, 
		const PS_TYPE& type,
		const COLOR_F& buf,
		const COLOR_F& subBuf = COLOR_F{});

private:

	//�V���O���g���̐���
	THIS_CLASS_IS_STATIC_SINGLETON(PixelShader);

	//���_���
	VERTEX2DSHADER vertex_[NUM_VERTEX];
	WORD index_[NUM_VERTEX_IDX];

	//�V�F�[�_�[�萔�o�b�t�@
	int psConstBuf_;

	//�V�F�[�_�[�̃��\�[�X�}�b�v
	std::unordered_map< PS_TYPE, int>psMap_;

	//�`��p�̎l�p���_�̍쐬
	void MakeSquereVertex(Vector2 pos, Vector2 size);

	//�V�F�[�_�[�̓ǂݍ���
	void InitPS();

	//�V�F�[�_�[�̌���
	const int& SearchPS(const PS_TYPE& ps)const;

	//�R���X�g���N�^
	PixelShader();

	//�f�X�g���N�^
	~PixelShader() = default;

};

