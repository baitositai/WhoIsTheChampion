#include "PlayerBase.h"
#include "../../Manager/ResourceManager.h"
#include "../../Manager/TextManager.h"
#include "../../Manager/InputManager.h"

PlayerBase::PlayerBase()
	: ps_(PixelShader::GetInstance())
{
	angle_ = -1.0f;
	animCnt_ = -1.0f;
	animNum_ = -1;
	animSpeed_ = -1.0f;
	dir_ = false;
	font_ = -1;
	name_ = L"";
	moveSpeed_ = -1.0f;
	rate_ = -1.0f;

	//分割画像初期化
	int value = -1;
	imgPlayer_ = &value;

	//各種変更処理の格納
	typeChanges_.emplace(DRAW_TYPE::NORMAL, std::bind(&PlayerBase::ChangeTypeNormal, this));
	typeChanges_.emplace(DRAW_TYPE::DIFF_COLOR, std::bind(&PlayerBase::ChangeTypeDiffColor, this));
}

PlayerBase::~PlayerBase()
{
}

void PlayerBase::Load()
{
	//プレイヤー画像
	imgPlayer_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::OMU_RUN).handleIds_;

	//フォント読み込み
	font_ = CreateFontToHandle(
		TextManager::GetInstance().GetFontName(TextManager::FONT_TYPE::HANAZOME).c_str(),
		FONT_SIZE,
		0);
}

void PlayerBase::Init()
{
#pragma region ステータス設定
	//初期位置
	pos_ = { FIRST_POS_X, FIRST_POS_Y };

	//プレイヤー拡大率
	rate_ = 1.0f;

	//プレイヤー回転
	angle_ = 0.0f;

	//プレイヤーサイズ
	size_ = { SIZE_X, SIZE_Y };

	//方向
	dir_ = false;

	//移動スピード
	moveSpeed_ = MOVE_SPEED;
#pragma endregion 

#pragma region アニメーション設定
	//アニメーションカウント
	animCnt_ = 0.0f;

	//アニメーション番号
	animNum_ = 0;

	//アニメーションスピード
	animSpeed_ = ANIM_SPEED;
#pragma endregion 

	//種類の初期化
	ChangeType(DRAW_TYPE::NORMAL);

}

void PlayerBase::Update()
{
	//アニメーション処理
	Animation();

	//種類の変更
	auto& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_RETURN))
	{
		//種類を変える
		int type = static_cast<int>(type_);
		type++;
		if (type == TYPE_MAX) { type = 0; }	//最大の場合最初に戻す
		type_ = static_cast<DRAW_TYPE>(type);
		ChangeType(type_);
	}
}

void PlayerBase::Draw()
{
	//種類別描画
	typeDraw_();

	//種類名の描画
	NameDraw();

	//デバッグ描画
	//DebagDraw();
}

void PlayerBase::Release()
{
	DeleteFontToHandle(font_);
}

void PlayerBase::ChangeType(const DRAW_TYPE type)
{
	// 状態受け取り
	type_ = type;

	// 各状態遷移の初期処理
	typeChanges_[type_]();
}

void PlayerBase::ChangeTypeNormal()
{
	typeDraw_ = std::bind(&PlayerBase::NormalDraw, this);
}

void PlayerBase::ChangeTypeDiffColor()
{
	typeDraw_ = std::bind(&PlayerBase::DiffColorDraw, this);
}

#pragma region typeDraw_に含まれるDraw関数

void PlayerBase::NormalDraw()
{
	name_ = L"通常";

	//プレイヤー
	DrawRotaGraph(
		pos_.x,
		pos_.y,
		rate_,
		angle_,
		imgPlayer_[animNum_],
		true,
		dir_
	);
}

void PlayerBase::DiffColorDraw()
{
	name_ = L"色違い";
	//ps_.DrawGraph(pos_.ToVector2(), imgPlayer_[animNum_]);

	auto& ds = PixelShader::GetInstance();
	COLOR_F buf;
	buf.r = 1.0f;
	buf.g = 1.0f;
	buf.b = 1.0f;
	buf.a = 1.0f;
	COLOR_F subBuf;
	subBuf.r = OMU_RUN_NUM_X;
	subBuf.g = OMU_RUN_NUM_Y;
	subBuf.b = animNum_;
	subBuf.a = 1.0f;

	Vector2 pos = pos_.ToVector2();
	pos.x -= SIZE_X *6/ 2;
	pos.y -= SIZE_Y / 2;

	ds.DrawExtendGraphToShader(
		{ pos.x ,pos.y },
		{ SIZE_X *6,SIZE_Y },
		imgPlayer_[animNum_],
		PixelShader::PS_TYPE::COL_TX,
		buf,
		subBuf
	);
}

#pragma endregion


void PlayerBase::NameDraw()
{
	DrawBox(
		0, 0,
		FONT_SIZE * name_.length(),
		FONT_SIZE,
		0xff0000,
		true
	);

	DrawFormatStringToHandle(
		0, 0,
		0xffffff,
		font_,
		name_.c_str()
	);
}

void PlayerBase::Animation()
{
	animCnt_ += animSpeed_;
	animNum_ = (int)animCnt_ % ANIM_RUN_NUM;
}

void PlayerBase::DebagDraw()
{
}
