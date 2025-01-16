
// �s�N�Z���V�F�[�_�[�̓���
struct PS_INPUT
{
	float4 Position : SV_POSITION; // ���W( �v���W�F�N�V������� )
	float4 Diffuse : COLOR0; // �f�B�t���[�Y�J���[
	float2 TexCoords0 : TEXCOORD0; // �e�N�X�`�����W
};

// �萔�o�b�t�@�F�X���b�g3�Ԗ�(b3�Ə���)
cbuffer cbParam : register(b3)
{
	float4 g_color;
	float g_num_x;
	float g_num_y;
	float g_animNum;
}

// �`�悷��e�N�X�`��
Texture2D g_SrcTexture : register(t0);//SetUseTextureToShader�łO�ɓ��ꂽ�e�N�X�`�����g�p

// �T���v���[�F�K�؂ȐF�����߂鏈��
SamplerState g_SrcSampler : register(s0);


float4 main(PS_INPUT PSInput) : SV_TARGET
{
	// �Ώۂ̉�f���擾
	float2 uv = PSInput.TexCoords0;

	// �e�N�X�`���͈͂𒲐�
	float2 adjustedUV = float2((1.0f / 6) * g_animNum, 0.0f) + uv * float2((1.0f / 6), 1.0f);

	float4 srcCol = g_SrcTexture.Sample(g_SrcSampler, adjustedUV);

	if (srcCol.a < 0.01f)
	{
		// �`�悵�Ȃ�
		discard;
	}

	//float4 srcCol = g_SrcTexture.Sample(TextureSampler, PSInput.TexCoords0);

	//�F�����]
	//srcCol = float4(1.0f - srcCol.r, 1.0f - srcCol.g, 1.0f - srcCol.b, 1.0f);
	
	//�O���[�X�P�[��
	//float mono = (srcCol.r + srcCol.g + srcCol.b) / 3;
	//srcCol = float4(mono, mono, mono, 1.0f);


	return srcCol * g_color;
}