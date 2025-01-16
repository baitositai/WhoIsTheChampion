#pragma once
#include "SceneBase.h"
#include "../framework.h"

class TitleScene : public SceneBase
{

public:

	//タイトルフォントサイズ
	static constexpr int MES_FONT_SIZE = 28;

	// コンストラクタ
	TitleScene(SceneManager& manager);

	// デストラクタ
	~TitleScene(void);

	void Load(void) override;
	void Init(void) override;
	void Update(InputManager& ins) override;
	void Draw(void) override;
	void Release(void) override;

private:	
	
	// タイトルロゴ
	int imgTitleLogo_;

	// メッセージフォント
	int mesFont_;

	// 更新関数
	void LoadingUpdate(InputManager& ins);
	void NormalUpdate(InputManager& ins);

	// 描画関数
	void LoadingDraw(void);
	void NormalDraw(void);
};