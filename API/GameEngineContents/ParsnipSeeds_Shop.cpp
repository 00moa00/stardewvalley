#include "ParsnipSeeds_Shop.h"

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

