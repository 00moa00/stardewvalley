#include "Dandelion_Shop.h"

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

	ShopItemListCollider_ = CreateCollision("Item", { 760, 73 });

	Index_ = static_cast<int>(SHOP_LIST::DANDELION);


}

void Dandelion_Shop::Update()
{
}

void Dandelion_Shop::InventoryNewItem()
{
}

