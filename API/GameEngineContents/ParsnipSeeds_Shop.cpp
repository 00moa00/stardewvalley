#include "ParsnipSeeds_Shop.h"
#include "Player.h"
#include "Parsnip_Seeds.h"

ParsnipSeeds_Shop::ParsnipSeeds_Shop() 
{
}

ParsnipSeeds_Shop::~ParsnipSeeds_Shop() 
{
}

void ParsnipSeeds_Shop::Start()
{
	ShopItemListRenderer_ = CreateRenderer("ParsnipSeeds_Shop.bmp");
	ShopItemListRenderer_->CameraEffectOff();

	ShopItemListCollider_ = CreateCollision("Item", { 760, 73 });

	Index_ = static_cast<int>(SHOP_LIST::PARSNIPSEEDS);
}

void ParsnipSeeds_Shop::Update()
{
}

void ParsnipSeeds_Shop::InventoryNewItem()
{
	Player* MainPlayer = MainPlayer = GetLevel()->FindActor<Player>("MainPlayer");
	MainPlayer->GetInventroy()->NewItem<Parsnip_Seeds>();
}

