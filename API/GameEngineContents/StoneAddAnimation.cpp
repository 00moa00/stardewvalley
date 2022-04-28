#include "StoneAddAnimation.h"

StoneAddAnimation::StoneAddAnimation() 
{
}

StoneAddAnimation::~StoneAddAnimation() 
{
}

void StoneAddAnimation::Start()
{
	EffectRenderer_ = CreateRenderer("StoneAnimationsSheet.bmp");
	EffectRenderer_->CreateAnimation("StoneAnimationsSheet.bmp", "ANIMATION", 0, 9, 0.08f, false);
	EffectRenderer_->ChangeAnimation("ANIMATION");
}

void StoneAddAnimation::Update()
{
	if (EffectRenderer_->IsEndAnimation())
	{
		this->Death();
	}
}

