#include "TreeTop.h"

TreeTop::TreeTop() 
{
}

TreeTop::~TreeTop() 
{
}

void TreeTop::Start()
{
	ItemRenderer_ = CreateRenderer();
	ItemRenderer_->CameraEffectOff();

	ItemCollider_ = CreateCollision("Item", { 40, 40 });
	ItemType_ = ITEMTYPE::ITEM;
}

void TreeTop::Update()
{
}

