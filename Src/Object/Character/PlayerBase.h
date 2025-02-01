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

	//操作主情報
	InputManager::JOYPAD_NO pad_;

	//状態別更新処理
	void UpdateNone()override;
	void UpdateActive()override;
	void UpdateDeath()override;

	//操作処理
	void ProcessMove();

	//ジャンプ処理
	void ProcessJump();

	
};

