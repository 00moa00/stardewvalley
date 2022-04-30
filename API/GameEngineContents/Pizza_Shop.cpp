#include "Pizza_Shop.h"
#include "Inventory.h"
#include "Pizza.h"

Pizza_Shop::Pizza_Shop() 
{
}

Pizza_Shop::~Pizza_Shop() 
{
}

void Pizza_Shop::Start()
{
	SetPosition({ 0.f,0.f });

	ShopItemListRenderer_ = CreateRenderer("Pizza_Shop.bmp");
	ShopItemListRenderer_->CameraEffectOff();

	ShopItemListCollider_ = CreateCollision("Pizza_Shop", { 760.f, 60.f });
	ShopItemListCollider_->SetPivot({ 0, +50.f / 2 });

	Index_ = static_cast<int>(SALOON_LIST::PIZZA);

	BuyPrice_ = 60;
}

void Pizza_Shop::Update()
{
}

void Pizza_Shop::InventoryNewItem()
{
	Inventory::MainInventory->NewItem<Pizza>();

}

bool Pizza_Shop::MouseInItem()
{
	return (ShopItemListCollider_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));
}
