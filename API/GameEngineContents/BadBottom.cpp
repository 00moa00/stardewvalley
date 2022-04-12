#include "BadBottom.h"

BadBottom::BadBottom() 
{
}

BadBottom::~BadBottom() 
{
}

void BadBottom::Start()
{
	ItemRenderer_ = CreateRenderer("BadBottom.bmp");
	ItemRenderer_->CameraEffectOff();
	ItemRenderer_->SetPivotType(RenderPivot::BOT);
	SetScale({ 96, 30 });
	///ItemRenderer_->SetPivot()
	//ItemCollider_ = CreateCollision("Item", { 40, 40 });
	ItemRenderer_->SetPivot({ GetPosition().x , GetPosition().y - 24.f });
	ItemType_ = ITEMTYPE::TOOL;
}

