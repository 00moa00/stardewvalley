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
	SubHPFont_ = GetLevel()->CreateActor<Font>(static_cast<int>(PLAYLEVEL::EFFECT));
	SubHPFont_->ChangeRedColor();

	MoveDir_ = {0, -120};

}

void SubHPFont::Update()
{
	MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 700.0f;
	if (this->GetPosition().y > PrevPos_.y)
	{
		this->Death();
	}
}

void SubHPFont::SetPosAndNum(float4 _Pos, int _Damage)
{
	SubHPFont_->ChangeNumItemLeftSort(_Damage, _Pos);
	PrevPos_ = _Pos;
}

