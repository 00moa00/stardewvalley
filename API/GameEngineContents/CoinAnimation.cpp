#include "CoinAnimation.h"
#include "CoinParticle.h"
CoinAnimation::CoinAnimation() 
	:
	Timer_(0.f),
	MoveDir_(float4::LEFT),
	TargetPos_(),
	CoinState_(COIN_STATE::COUNT),
	Coin_(nullptr)
{
}

CoinAnimation::~CoinAnimation() 
{
}

void CoinAnimation::Start()
{
	
}

void CoinAnimation::Update()
{

	switch (CoinState_)
	{
	case COIN_STATE::COUNT:

		Timer_ += GameEngineTime::GetInst()->GetDeltaTime();
		if (Timer_ > 0.1f)
		{
			Timer_ = 0.f;
			CoinState_ = COIN_STATE::CREATE;
		}

		break;
	case COIN_STATE::CREATE:
		
		Coin_ =  GetLevel()->CreateActor<CoinParticle>(static_cast<int>(PLAYLEVEL::SHOP_EFFECT));
		Coin_->SetPosition(this->GetPosition());
		Coin_ = nullptr;
		--Count_;
		if (Count_ <= 0)
		{
			this->Death();
		}
		CoinState_ = COIN_STATE::COUNT;

		break;
	default:
		break;
	}


}

