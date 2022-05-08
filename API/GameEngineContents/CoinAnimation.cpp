#include "CoinAnimation.h"

CoinAnimation::CoinAnimation() 
	:
	MoveDir_(float4::LEFT),
	TargetPos_()
{
}

CoinAnimation::~CoinAnimation() 
{
}

void CoinAnimation::Start()
{
	EffectRenderer_ = CreateRenderer("Coin.bmp");
	TargetPos_ = { 250.f, 475.f };
}

void CoinAnimation::Update()
{
	float4 MoveTarget = TargetPos_ - this->GetPosition();

	SetMove(MoveTarget * GameEngineTime::GetInst()->GetDeltaTime() * 120.f);
	if (this->GetPosition().y < TargetPos_.y)
	{
		this->Death();
	}

}

