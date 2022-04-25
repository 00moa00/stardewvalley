#include "WateringCanEffect.h"

WateringCanEffect::WateringCanEffect() 
{
}

WateringCanEffect::~WateringCanEffect() 
{
}

void WateringCanEffect::Start()
{
	EffectRenderer_ = CreateRenderer("WateringCanAnimations.bmp");
	EffectRenderer_->CreateAnimation("WateringCanAnimations.bmp", "ANIMATION", 0, 9, 0.08f, false);
	EffectRenderer_->ChangeAnimation("ANIMATION");
}

void WateringCanEffect::Update()
{
	if (EffectRenderer_->IsEndAnimation())
	{
		this->Death();
	}
}

