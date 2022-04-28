#include "WoodAddAnimaition.h"

WoodAddAnimaition::WoodAddAnimaition() 
{
}

WoodAddAnimaition::~WoodAddAnimaition() 
{
}

void WoodAddAnimaition::Start()
{
	EffectRenderer_ = CreateRenderer("WoodAnimationsSheet.bmp");
	EffectRenderer_->CreateAnimation("WoodAnimationsSheet.bmp", "ANIMATION", 0, 9, 0.150f, false);
	EffectRenderer_->ChangeAnimation("ANIMATION");
}

void WoodAddAnimaition::Update()
{
	if (EffectRenderer_->IsEndAnimation())
	{
		this->Death();
	}
}

