#include "KiraEffect.h"

KiraEffect::KiraEffect() 
{
}

KiraEffect::~KiraEffect() 
{
}

void KiraEffect::Start()
{
	EffectRenderer_ = CreateRenderer("KiraAnimation.bmp");
	EffectRenderer_->CreateAnimation("KiraAnimation.bmp", "ANIMATION", 0, 9, 0.150f, false);
	EffectRenderer_->ChangeAnimation("ANIMATION");
}

void KiraEffect::Update()
{

	if (EffectRenderer_->IsEndAnimation())
	{
		this->Death();
	}
}

