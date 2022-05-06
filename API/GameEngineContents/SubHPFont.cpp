#include "SubHPFont.h"
#include "RendererData.h"
SubHPFont::SubHPFont() 
	:
	MoveDir_(),

	SubHPFont_(nullptr)
{
}

SubHPFont::~SubHPFont() 
{
}

void SubHPFont::Start()
{
	SetPosition({ 0,0 });
	SubHPFont_ = GetLevel()->CreateActor<Font>(static_cast<int>(PLAYLEVEL::EFFECT));
	SubHPFont_->ChangeRedColor();
	SubHPFont_->SetFontCameraEffectOn();
}

void SubHPFont::Update()
{
	MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 700;
	SubHPFont_->SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());

	if (SubHPFont_->GetPosition().y > PrevPos_.y)
	{
		SubHPFont_->Death();
		this->Death();
	}
}

void SubHPFont::SetPosAndNumRed(float4 _Pos, int _Damage)
{
	SubHPFont_->SetPosition({ _Pos.x, _Pos.y - 48.f});
	SubHPFont_->ChangeRedColor();
	SubHPFont_->ChangeNumRightSort(_Damage);
	MoveDir_ = { 0, -150 };


	PrevPos_ = { _Pos.x, _Pos.y - 48.f };
}

void SubHPFont::SetPosAndNumGray(float4 _Pos, int _Damage)
{
	SubHPFont_->SetPosition({ _Pos.x, _Pos.y - 48.f });
	SubHPFont_->ChangeGrayColor();
	SubHPFont_->ChangeNumRightSort(_Damage);
	MoveDir_ = { 0, -150 };


	PrevPos_ = { _Pos.x, _Pos.y - 48.f };
}

