#include "ShopFlag.h"

ShopFlag::ShopFlag() 
{
}

ShopFlag::~ShopFlag() 
{
}

void ShopFlag::Start()
{
	ItemRenderer_ = CreateRenderer("block.bmp");
	ItemRenderer_->SetPivotType(RenderPivot::CENTER);
	
	ItemCollider_ = CreateCollision("ShopFlag", { 0, 0 });
	
	//ItemType_ = ITEMTYPE::BLOCK;
}

