#include "StoneCrushAnimation.h"

StoneCrushAnimation::StoneCrushAnimation() 
{
}

StoneCrushAnimation::~StoneCrushAnimation() 
{
}

void StoneCrushAnimation::Start()
{
	EffectRenderer_ = CreateRenderer("StoneAnimationsSheet.bmp");
	EffectRenderer_->CreateAnimation("StoneAnimationsSheet.bmp", "ANIMATION", 0, 9, 0.08f, false);
	EffectRenderer_->ChangeAnimation("ANIMATION");
}

void StoneCrushAnimation::Update()
{
	if (EffectRenderer_->IsEndAnimation())
	{
		this->Death();
	}
}

