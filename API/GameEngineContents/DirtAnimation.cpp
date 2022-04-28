#include "DirtAnimation.h"

DirtAnimation::DirtAnimation() 
{
}

DirtAnimation::~DirtAnimation() 
{
}

void DirtAnimation::Start()
{
	EffectRenderer_ = CreateRenderer("DirtAnimations.bmp");
	EffectRenderer_->CreateAnimation("DirtAnimations.bmp", "ANIMATION", 0, 9, 0.08f, false);
	EffectRenderer_->ChangeAnimation("ANIMATION");
}

void DirtAnimation::Update()
{
	if (EffectRenderer_->IsEndAnimation())
	{
		this->Death();
	}
}

