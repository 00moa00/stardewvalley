#include "TreeBottom.h"

TreeBottom::TreeBottom() 
{
}

TreeBottom::~TreeBottom() 
{
}

void TreeBottom::Start()
{
	ItemRenderer_ = CreateRenderer();
	ItemRenderer_->CameraEffectOff();

	ItemCollider_ = CreateCollision("Item", { 40, 40 });
	ItemType_ = ITEMTYPE::ITEM;

}

void TreeBottom::Update()
{
}

