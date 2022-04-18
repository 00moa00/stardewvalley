#include "JazzSeeds_Shop.h"

JazzSeeds_Shop::JazzSeeds_Shop() 
{
}

JazzSeeds_Shop::~JazzSeeds_Shop() 
{
}

void JazzSeeds_Shop::Start()
{
	ShopItemListRenderer_ = CreateRenderer("JazzSeeds_Shop.bmp");
	ShopItemListRenderer_->CameraEffectOff();

	ShopItemListCollider_ = CreateCollision("JazzSeeds_Shop", { 760, 73 });

	Index_ = static_cast<int>(SHOP_LIST::JAZZSEEDS);

	BuyPrice_ = 30;

}

void JazzSeeds_Shop::Update()
{
}

void JazzSeeds_Shop::InventoryNewItem()
{
}

bool JazzSeeds_Shop::MouseInItem()
{
	return (ShopItemListCollider_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));
}

