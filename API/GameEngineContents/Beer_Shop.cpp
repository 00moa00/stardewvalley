#include "Beer_Shop.h"
#include "Inventory.h"
#include "Beer.h"

Beer_Shop::Beer_Shop() 
{
}

Beer_Shop::~Beer_Shop() 
{
}

void Beer_Shop::Start()
{
	SetPosition({ 0.f,0.f });

	ShopItemListRenderer_ = CreateRenderer("Beer_Shop.bmp");
	ShopItemListRenderer_->CameraEffectOff();

	ShopItemListCollider_ = CreateCollision("Beer_Shop", { 760.f, 60.f });
	ShopItemListCollider_->SetPivot({ 0, +50.f / 2 });

	Index_ = static_cast<int>(SALOON_LIST::BEER);

	BuyPrice_ = 60;
}

void Beer_Shop::Update()
{
}

void Beer_Shop::InventoryNewItem()
{
	Inventory::MainInventory->NewItem<Beer>();
}

bool Beer_Shop::MouseInItem()
{
	return (ShopItemListCollider_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));
}
