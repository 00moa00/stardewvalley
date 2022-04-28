#include "FlowerParticles.h"

FlowerParticles::FlowerParticles() 
	:
	RandomAnimation_()
{
}

FlowerParticles::~FlowerParticles() 
{
}

void FlowerParticles::Start()
{
	EffectRenderer_ = CreateRenderer("Flower.bmp");

	EffectRenderer_->CreateAnimation("Flower.bmp", "ANIMATION00", 0, 10, 0.200f, true);
	EffectRenderer_->CreateAnimation("Flower.bmp", "ANIMATION01", 0, 10, 0.150f, true);
	EffectRenderer_->CreateAnimation("Flower.bmp", "ANIMATION02", 0, 10, 0.200f, true);
	EffectRenderer_->CreateAnimation("Flower.bmp", "ANIMATION03", 0, 10, 0.120f, true);
	EffectRenderer_->CreateAnimation("Flower.bmp", "ANIMATION04", 0, 10, 0.200f, true);



	EffectRenderer_->ChangeAnimation("ANIMATION00");
	//EffectRenderer_->CameraEffectOff();
}

void FlowerParticles::Update()
{
	SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);
	SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * Speed_);

	if (this->GetPosition().y > MaxY_)
	{
		this->Death();
	}

}

void FlowerParticles::SetRandomAnimation(float _MaxY)
{
	MaxY_ = _MaxY;
	Speed_ = RandomSpeed_.RandomFloat(70.f, 90.f);
	int Animation = RandomAnimation_.RandomInt(0, 4);

	switch (Animation)
	{

	case 0 :
		EffectRenderer_->ChangeAnimation("ANIMATION00");
		break;
	case 1 :
		EffectRenderer_->ChangeAnimation("ANIMATION01");

		break;
	case 2 :
		EffectRenderer_->ChangeAnimation("ANIMATION02");

		break;
	case 3 :
		EffectRenderer_->ChangeAnimation("ANIMATION03");

		break;
	case 4:
		EffectRenderer_->ChangeAnimation("ANIMATION04");

		break;

	default:
		break;
	}
}

