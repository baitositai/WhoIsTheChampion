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
Texture2D g_FadeTexture : register(t1);

//�T���v���[�F�K�؂ȐF�����߂�
SamplerState g_SrcSampler : register(s0);

//�萔�o�b�t�@�F�X���b�g�ԍ�3�Ԗځib3�j
cbuffer cbParam : register(b3)
{
    float g_pra;
}

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//UV���W���󂯎��
    float2 uv = PSInput.TexCoords0;

	//UV���W�ƃe�N�X�`�����Q�Ƃ��āA�œK�ȐF���擾����
    float4 srcCol =
		g_SrcTexture.Sample(g_SrcSampler, uv);
    float4 fadeCol =
		g_FadeTexture.Sample(g_SrcSampler, uv);

	//�A���t�@�l
    float alpha = 1.0f - (fadeCol.r + fadeCol.g + fadeCol.b) / 3.0f;
    alpha -= 1.0;                   //{0.0f}�`{-1.0f}�̏�Ԃɂ���
    alpha += (g_pra * 2.0f);        //{0.0f}�`{2.0f}�̎��Ԋ��������Z����

    return float4(srcCol.rgb, srcCol.a * alpha);
}