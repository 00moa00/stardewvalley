#include "PatatoSeeds_Shop.h"
#include "Player.h"
#include "Potato_Seeds.h"

PatatoSeeds_Shop::PatatoSeeds_Shop() 
{
}

PatatoSeeds_Shop::~PatatoSeeds_Shop() 
{
}

void PatatoSeeds_Shop::Start()
{
	ShopItemListRenderer_ = CreateRenderer("PatatoSeeds_Shop.bmp");
	ShopItemListRenderer_->CameraEffectOff();

	ShopItemListCollider_ = CreateCollision("PatatoSeeds_Shop", { 760, 73 });

	Index_ = static_cast<int>(SHOP_LIST::PATAPOSEEDS);
	
	BuyPrice_ = 50;

}

void PatatoSeeds_Shop::Update()
{
}

void PatatoSeeds_Shop::InventoryNewItem()
{
	Player::MainPlayer->GetInventroy()->NewItem<Potato_Seeds>();
}

bool PatatoSeeds_Shop::MouseInItem()
{
	return (ShopItemListCollider_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));
}

