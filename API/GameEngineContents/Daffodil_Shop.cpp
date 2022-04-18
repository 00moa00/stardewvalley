#include "Daffodil_Shop.h"

Daffodil_Shop::Daffodil_Shop() 
{
}

Daffodil_Shop::~Daffodil_Shop() 
{
}

void Daffodil_Shop::Start()
{
	ShopItemListRenderer_ = CreateRenderer("Daffodil_Shop.bmp");
	ShopItemListRenderer_->CameraEffectOff();

	ShopItemListCollider_ = CreateCollision("Daffodil_Shop", { 760, 73 });

	Index_ = static_cast<int>(SHOP_LIST::DAFFODIL);

	BuyPrice_ = 35;
}

void Daffodil_Shop::Update()
{
}

void Daffodil_Shop::InventoryNewItem()
{
}

bool Daffodil_Shop::MouseInItem()
{
	return (ShopItemListCollider_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));
}

