//�s�N�Z���V�F�[�_�[�̓���
struct PS_INPUT
{
	//���W�i�v���W�F�N�V������ԁj
    float4 Position : SV_POSITION;
	//�f�B�t�[�Y�J���[
    float4 Diffuse : COLORO;
	//�e�N�X�`�����W
    float2 TexCoords0 : TEXCOORD0;
};

//�`�悷��e�N�X�`��
Texture2D g_SrcTexture : register(t0);

//�T���v���[�F�K�؂ȐF�����߂�
SamplerState g_SrcSampler : register(s0);

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//UV���W���󂯎��
    float2 uv = PSInput.TexCoords0;

	//UV���W�ƃe�N�X�`�����Q�Ƃ��āA�œK�ȐF���擾����
    float4 srcCol =
		g_SrcTexture.Sample(g_SrcSampler, uv);

    return srcCol;
}