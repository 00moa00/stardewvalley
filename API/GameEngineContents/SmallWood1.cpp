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
	ItemCollider_ = CreateCollision("MapObject", { 40, 40 });

	ItemCollider_ = CreateCollision("MapObject", { 48.f, 48.f });

	ItemType_ = ITEMTYPE::ITEM;
	ItemName_ = "SmallWood1";

}

void SmallWood1::Update()
{
}

