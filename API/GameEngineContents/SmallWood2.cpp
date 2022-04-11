#include "SmallWood2.h"

SmallWood2::SmallWood2() 
{
}

SmallWood2::~SmallWood2() 
{
}

void SmallWood2::Start()
{
	ItemRenderer_ = CreateRenderer("Small_Wood2.bmp");
	//ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::WILD_HORSERADISH));
	//ItemRenderer_->CameraEffectOff();
	ItemRenderer_->SetPivotType(RenderPivot::BOT);
	SetScale({ 35.f, 48.f });
	ItemCollider_ = CreateCollision("Object", { 100, 400 });
	ItemType_ = ITEMTYPE::ITEM;
}

void SmallWood2::Update()
{
}

