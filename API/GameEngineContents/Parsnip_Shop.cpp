#include "Parsnip_Shop.h"
#include "Pasnip.h"
#include "Inventory.h"
Parsnip_Shop* Parsnip_Shop::MainParsnipShop = nullptr;

Parsnip_Shop::Parsnip_Shop() 
{
}

Parsnip_Shop::~Parsnip_Shop() 
{
}

void Parsnip_Shop::Start()
{
	SetPosition({ 0.f,0.f });

	ShopItemListRenderer_ = CreateRenderer("Parsnip_Shop.bmp");
	ShopItemListRenderer_->CameraEffectOff();

	ShopItemListCollider_ = CreateCollision("Parsnip_Shop", { 760, 60 });
	ShopItemListCollider_->SetPivot({ 0, +50.f / 2 });

	Index_ = static_cast<int>(SHOP_LIST::PARSNIP);

	BuyPrice_ = 35;

}


void Parsnip_Shop::Update()
{
}

void Parsnip_Shop::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainParsnipShop = this;
}

void Parsnip_Shop::InventoryNewItem()
{
	Inventory::MainInventory->NewItem<Pasnip>();
}

bool Parsnip_Shop::MouseInItem()
{
	return (ShopItemListCollider_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));
}

