#include "JazzSeeds_Shop.h"

JazzSeeds_Shop::JazzSeeds_Shop() 
{
}

JazzSeeds_Shop::~JazzSeeds_Shop() 
{
}

void JazzSeeds_Shop::Start()
{
	ShopItemListRenderer_ = CreateRenderer("JazzSeeds_Shop.bmp");
	ShopItemListRenderer_->CameraEffectOff();

	ShopItemListCollider_ = CreateCollision("Item", { 760, 73 });

	Index_ = static_cast<int>(SHOP_LIST::JAZZSEEDS);


}

void JazzSeeds_Shop::Update()
{
}

void JazzSeeds_Shop::InventoryNewItem()
{
}

