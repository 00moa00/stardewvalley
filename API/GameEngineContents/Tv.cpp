#include "Tv.h"

Tv::Tv() 
{
}

Tv::~Tv() 
{
}

void Tv::Start()
{
	ItemRenderer_ = CreateRenderer("Tv.bmp");
	ItemRenderer_->CameraEffectOff();
	SetScale({ 90, 132 });
	//ItemRenderer_->SetPivotType(RenderPivot::BOT);
	ItemRenderer_->SetPivot({ GetPosition().x + 24.f, GetPosition().y});
	//ItemCollider_ = CreateCollision("Item", { 40, 40 });
	ItemType_ = ITEMTYPE::TOOL;
}

