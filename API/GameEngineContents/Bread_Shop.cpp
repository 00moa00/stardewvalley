#include "Bread_Shop.h"
#include "Inventory.h"
#include "Bread.h"

Bread_Shop::Bread_Shop() 
{
}

Bread_Shop::~Bread_Shop() 
{
}

void Bread_Shop::Start()
{
	SetPosition({ 0.f,0.f });

	ShopItemListRenderer_ = CreateRenderer("Bread_Shop.bmp");
	ShopItemListRenderer_->CameraEffectOff();

	ShopItemListCollider_ = CreateCollision("Bread_Shop", { 760.f, 60.f });
	ShopItemListCollider_->SetPivot({ 0, +50.f / 2 });

	Index_ = static_cast<int>(SALOON_LIST::BREAD);

	BuyPrice_ = 60;
}

void Bread_Shop::Update()
{
}

void Bread_Shop::InventoryNewItem()
{
	Inventory::MainInventory->NewItem<Bread>();
}

bool Bread_Shop::MouseInItem()
{
	return (ShopItemListCollider_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));
}
