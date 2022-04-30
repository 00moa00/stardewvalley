#include "Spaghetti_Shop.h"
#include "Inventory.h"
Spaghetti_Shop::Spaghetti_Shop() 
{
}

Spaghetti_Shop::~Spaghetti_Shop() 
{
}

void Spaghetti_Shop::Start()
{
	SetPosition({ 0.f,0.f });

	ShopItemListRenderer_ = CreateRenderer("Spaghetti_Shop.bmp");
	ShopItemListRenderer_->CameraEffectOff();

	ShopItemListCollider_ = CreateCollision("Spaghetti_Shop", { 760.f, 60.f });
	ShopItemListCollider_->SetPivot({ 0, +50.f / 2 });

	Index_ = static_cast<int>(SALOON_LIST::SPAGHETTI);

	BuyPrice_ = 60;
}

void Spaghetti_Shop::Update()
{
}

void Spaghetti_Shop::InventoryNewItem()
{
	//Inventory::MainInventory->NewItem<Bean_Seeds>();
}

bool Spaghetti_Shop::MouseInItem()
{
	return (ShopItemListCollider_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));
}
