#include "JazzSeeds_Shop.h"
#include "Jazz_Seeds.h"
#include "Player.h"

JazzSeeds_Shop::JazzSeeds_Shop() 
{
}

JazzSeeds_Shop::~JazzSeeds_Shop() 
{
}

void JazzSeeds_Shop::Start()
{
	SetPosition({ 0.f,0.f });

	ShopItemListRenderer_ = CreateRenderer("JazzSeeds_Shop.bmp");
	ShopItemListRenderer_->CameraEffectOff();

	ShopItemListCollider_ = CreateCollision("JazzSeeds_Shop", { 760.f, 73.f });
	ShopItemListCollider_->SetPivot({ 0, +50.f / 2 });

	Index_ = static_cast<int>(SHOP_LIST::JAZZSEEDS);

	BuyPrice_ = 30;

}

void JazzSeeds_Shop::Update()
{
}

void JazzSeeds_Shop::InventoryNewItem()
{
	Inventory::MainInventory->NewItem<Jazz_Seeds>();

}

bool JazzSeeds_Shop::MouseInItem()
{
	return (ShopItemListCollider_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));
}

