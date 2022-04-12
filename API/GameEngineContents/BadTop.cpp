#include "BadTop.h"

BadTop::BadTop() 
{
}

BadTop::~BadTop() 
{
}

void BadTop::Start()
{
	ItemRenderer_ = CreateRenderer("Bad.bmp");
	ItemRenderer_->CameraEffectOff();
	//SetScale({ 96, 111 });
	ItemRenderer_->SetPivotType(RenderPivot::BOT);
	//ItemCollider_ = CreateCollision("Item", { 40, 40 });
	ItemRenderer_->SetPivot({ GetPosition().x , GetPosition().y - 24.f });
	ItemType_ = ITEMTYPE::TOOL;
}

