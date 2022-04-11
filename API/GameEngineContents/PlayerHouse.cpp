#include "PlayerHouse.h"

PlayerHouse::PlayerHouse() 
{
}

PlayerHouse::~PlayerHouse() 
{
}

void PlayerHouse::Start()
{
	ItemRenderer_ = CreateRenderer("house.bmp");
	//ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::WILD_HORSERADISH));
	//ItemRenderer_->CameraEffectOff();
	ItemRenderer_->SetPivotType(RenderPivot::CENTER);
	//ItemRenderer_->SetPivot();
	SetScale({ 300, 300 });
	//ItemCollider_ = CreateCollision("Object", { 100, 400 });
	ItemType_ = ITEMTYPE::ITEM;

}

void PlayerHouse::Update()
{
}

