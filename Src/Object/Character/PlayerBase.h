#pragma once
#include "../../framework.h"
#include "../../Application.h"
#include "../../Common/Vector2.h"
#include "../../Common/Vector2F.h"
#include "../../Manager/ResourceManager.h"
#include "../../Manager/InputManager.h"
#include "../../Shader/PixelShader.h"
#include "CharacterBase.h"

class PlayerBase : public CharacterBase
{
public:
	
	PlayerBase();
	~PlayerBase();

	void Load() override;
	//void Draw()override;

private:

	//‘€ìåî•ñ
	InputManager::JOYPAD_NO pad_;

	//ó‘Ô•ÊXVˆ—
	void UpdateNone()override;
	void UpdateActive()override;
	void UpdateDeath()override;

	//‘€ìˆ—
	void ProcessMove();
};