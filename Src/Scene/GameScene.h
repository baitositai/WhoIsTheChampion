#pragma once
#include "../framework.h"
#include "SceneBase.h"

class PlayerBase;
class CharacterBase;
class StageBase;

class GameScene : public SceneBase
{
public:

	// コンストラクタ
	GameScene(SceneManager& manager);

	// デストラクタ
	~GameScene(void);

	void Load(void) override;
	void Init(void) override;
	void Update(InputManager& input) override;
	void Draw(void) override;
	void Release(void) override;

private:	
	
	// プレイヤー(キャラクター)
	std::unique_ptr<PlayerBase> player_;

	//ステージ
	std::unique_ptr<StageBase> stage_;

	//Update関数
	void LoadingUpdate(InputManager& ins);
	void NormalUpdate(InputManager& ins);

	//描画関数 
	void LoadingDraw(void);
	void NormalDraw(void);

	//デバッグ描画
	void DebagDraw();
};

