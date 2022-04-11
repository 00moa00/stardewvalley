#include "SmallStone.h"

SmallStone::SmallStone() 
{
}

SmallStone::~SmallStone() 
{
}

void SmallStone::Start()
{


	ItemRenderer_ = CreateRenderer("Small_Stone.bmp");
	//ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::WILD_HORSERADISH));
	//ItemRenderer_->CameraEffectOff();
	ItemRenderer_->SetPivotType(RenderPivot::BOT);
	SetScale({ 48.f, 48.f });
	//ItemCollider_ = CreateCollision("Object", { 30, 30 });
	ItemType_ = ITEMTYPE::ITEM;
}

void SmallStone::Update()
{


}

