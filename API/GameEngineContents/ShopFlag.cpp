#include "ShopFlag.h"
//ShopFlag* ShopFlag::MainShopFlag;

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
	ItemCollider_ = CreateCollision("ShopFlag", { 48, 48 });

}

void ShopFlag::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
//	MainShopFlag = this;
}

