#include "PatatoSeeds_Shop.h"
#include "Player.h"

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

	ShopItemListCollider_ = CreateCollision("Item", { 760, 73 });

	Index_ = static_cast<int>(SHOP_LIST::PATAPOSEEDS);

}

void PatatoSeeds_Shop::Update()
{
}

void PatatoSeeds_Shop::InventoryNewItem()
{
	//Player* MainPlayer = MainPlayer = GetLevel()->FindActor<Player>("MainPlayer");
	//MainPlayer->GetInventroy()->NewItem<PatatoSeeds_Shop>();
}

