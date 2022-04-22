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
	ShopItemListRenderer_ = CreateRenderer("Dandelion_Shop.bmp");
	ShopItemListRenderer_->CameraEffectOff();

	ShopItemListCollider_ = CreateCollision("Dandelion_Shop", { 760, 73 });

	Index_ = static_cast<int>(SHOP_LIST::DANDELION);

	BuyPrice_ = 40;
}

void Dandelion_Shop::Update()
{
}

void Dandelion_Shop::InventoryNewItem()
{
	Player::MainPlayer->GetInventroy()->NewItem<Dandelion>();

}

bool Dandelion_Shop::MouseInItem()
{
	return (ShopItemListCollider_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));
}

