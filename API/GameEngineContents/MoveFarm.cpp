#include "MoveFarm.h"

MoveFarm::MoveFarm() 
{
}

MoveFarm::~MoveFarm() 
{
}

void MoveFarm::Start()
{
	ItemRenderer_ = CreateRenderer("block.bmp");
	//ItemRenderer_->CameraEffectOff();
	ItemRenderer_->SetPivotType(RenderPivot::CENTER);
	//SetScale({ 48.f, 48.f });
	ItemCollider_ = CreateCollision("MoveFarm", { 48, 24 });
	ItemType_ = ITEMTYPE::BLOCK;
}

