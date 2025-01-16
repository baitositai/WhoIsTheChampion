#include <math.h>
#include "Vector2.h"
#include "Vector2F.h"


//�f�t�H���g�R���X�g���N�^
Vector2F::Vector2F(void)
{
	x = 0.0F;
	y = 0.0F;
}


//�R���X�g���N�^
Vector2F::Vector2F(float ix, float iy)
{
	x = ix;
	y = iy;
}


//�f�X�g���N�^
Vector2F::~Vector2F(void)
{

}


//Vector2�֕ϊ�����֐�
Vector2 Vector2F::ToVector2(void)
{
	Vector2 ret;

	ret.x = static_cast<int>(roundf(x));
	ret.y = static_cast<int>(roundf(y));

	return ret;
}

//�x�N�g���������
Vector2F Vector2F::CreateVectorLine(Vector2 value1, Vector2 value2)
{
	return Vector2F(static_cast<float>(value1.x - value2.x),
		static_cast<float>(value1.y - value2.y));
}

//Vector2F���m�̔�r
bool Vector2F::IsVector2F(Vector2F value1, Vector2F value2)
{
	if (value1.x < value2.x &&
		value1.y < value2.y)
	{
		return true;
	}

	return false;
}
