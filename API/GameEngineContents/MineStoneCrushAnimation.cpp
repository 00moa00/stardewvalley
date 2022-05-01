#include "MineStoneCrushAnimation.h"

MineStoneCrushAnimation::MineStoneCrushAnimation() 
	:
	DeathTimer_(0.f)
{
}

MineStoneCrushAnimation::~MineStoneCrushAnimation() 
{
}

void MineStoneCrushAnimation::Start()
{
	EffectRenderer_ = CreateRenderer("springobjects.bmp");
	EffectRenderer_->SetIndex(static_cast<int>(ITEM::STONE0_PARTICLE));
}

void MineStoneCrushAnimation::Update()
{
	DeathTimer_ += GameEngineTime::GetDeltaTime();
	if (DeathTimer_ > 0.5f)
	{
		this->Death();
	}
}

void MineStoneCrushAnimation::SetImageIndex(ITEM _ItemCode)
{
	EffectRenderer_->SetIndex(static_cast<int>(_ItemCode));

}

