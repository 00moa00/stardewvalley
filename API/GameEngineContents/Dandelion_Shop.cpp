#include "Dandelion_Shop.h"
#include "Dandelion.h"
#include "Player.h"

Dandelion_Shop::Dandelion_Shop() 
{
}

Dandelion_Shop::~Dandelion_Shop() 
{
}

void Dandelion_Shop::Start()
{
	SetPosition({ 0.f,0.f });

	ShopItemListRenderer_ = CreateRenderer("Dandelion_Shop.bmp");
	ShopItemListRenderer_->CameraEffectOff();

	ShopItemListCollider_ = CreateCollision("Dandelion_Shop", { 760, 73 });
	ShopItemListCollider_->SetPivot({ 0, +50.f / 2 });

	Index_ = static_cast<int>(SHOP_LIST::DANDELION);

	BuyPrice_ = 40;
}

void Dandelion_Shop::Update()
{
}

void Dandelion_Shop::InventoryNewItem()
{
	Inventory::MainInventory->NewItem<Dandelion>();

}

bool Dandelion_Shop::MouseInItem()
{
	return (ShopItemListCollider_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));
}

