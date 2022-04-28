#include "StoneAddAnimation.h"

StoneAddAnimation::StoneAddAnimation() 
{
}

StoneAddAnimation::~StoneAddAnimation() 
{
}

void StoneAddAnimation::Start()
{
	EffectRenderer_ = CreateRenderer("KiraAnimation.bmp");
	EffectRenderer_->CreateAnimation("KiraAnimation.bmp", "ANIMATION", 0, 9, 0.150f, false);
	EffectRenderer_->ChangeAnimation("ANIMATION");
}

void StoneAddAnimation::Update()
{
	if (EffectRenderer_->IsEndAnimation())
	{
		this->Death();
	}
}

