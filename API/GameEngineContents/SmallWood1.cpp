#include "SmallWood1.h"

SmallWood1::SmallWood1() 
{
}

SmallWood1::~SmallWood1() 
{
}

void SmallWood1::Start()
{
	ItemRenderer_ = CreateRenderer("Small_Wood1.bmp");
	//ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::WILD_HORSERADISH));
	//ItemRenderer_->CameraEffectOff();
	ItemRenderer_->SetPivotType(RenderPivot::BOT);
	SetScale({ 35.f, 48.f });
	ItemCollider_ = CreateCollision("Object", { 100, 400 });
	ItemType_ = ITEMTYPE::ITEM;
	ItemName_ = "SmallWood1";

}

void SmallWood1::Update()
{
}

