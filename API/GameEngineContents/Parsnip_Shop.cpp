#include "Parsnip_Shop.h"

Parsnip_Shop::Parsnip_Shop() 
{
}

Parsnip_Shop::~Parsnip_Shop() 
{
}

void Parsnip_Shop::Start()
{
	ShopItemListRenderer_ = CreateRenderer("Parsnip_Shop.bmp");
	ShopItemListRenderer_->CameraEffectOff();

	ShopItemListCollider_ = CreateCollision("Parsnip_Shop", { 760, 73 });

	Index_ = static_cast<int>(SHOP_LIST::PARSNIP);

	BuyPrice_ = 35;

}


void Parsnip_Shop::Update()
{
}

void Parsnip_Shop::InventoryNewItem()
{
}

bool Parsnip_Shop::MouseInItem()
{
	return (ShopItemListCollider_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));
}

