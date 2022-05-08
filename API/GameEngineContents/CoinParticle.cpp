#include "CoinParticle.h"

CoinParticle::CoinParticle() 
{
}

CoinParticle::~CoinParticle() 
{
}

void CoinParticle::Start()
{
	EffectRenderer_ = CreateRenderer("Coin.bmp");
	EffectRenderer_->CameraEffectOff();
	TargetPos_ = { 250.f, 475.f };
}

void CoinParticle::Update()
{
	float4 MoveTarget = TargetPos_ - this->GetPosition();

	SetMove(MoveTarget * GameEngineTime::GetInst()->GetDeltaTime() * 15.f);
	if (this->GetPosition().x <= TargetPos_.x + 20.f)
	{
		this->Death();
	}

}

