#include "MoveHouse.h"

MoveHouse::MoveHouse() 
{
}

MoveHouse::~MoveHouse() 
{
}

void MoveHouse::Start()
{
	ItemRenderer_ = CreateRenderer("block.bmp");
	//ItemRenderer_->CameraEffectOff();
	ItemRenderer_->SetPivotType(RenderPivot::CENTER);
	//SetScale({ 48.f, 48.f });
	ItemCollider_ = CreateCollision("MoveHouse", { 48, 48 });
	ItemType_ = ITEMTYPE::FALG;
}

