#pragma once

class Vector2;

class Vector2F
{
public:

	//�f�t�H���g�R���X�g���N�^
	Vector2F(void);

	//�R���X�g���N�^
	Vector2F(float ix, float iy);

	//�f�X�g���N�^
	~Vector2F(void);

	//Vector2�֕ϊ�����֐�
	Vector2 ToVector2(void);

	//�x�N�g���������
	Vector2F CreateVectorLine(Vector2 value1, Vector2 value2);

	//Vector2F���m�̔�r
	bool IsVector2F(Vector2F value1, Vector2F value2);

	float x;
	float y;

private:
};