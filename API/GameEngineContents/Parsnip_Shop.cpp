#include "Parsnip_Shop.h"

Parsnip_Shop::Parsnip_Shop() 
{
}

Parsnip_Shop::~Parsnip_Shop() 
{
}

void Parsnip_Shop::Start()
{
	ShopItemListRenderer_ = CreateRenderer("Parsnip_Shop.bmp");
	ShopItemListRenderer_->CameraEffectOff();

	ShopItemListCollider_ = CreateCollision("Item", { 760, 73 });

	Index_ = static_cast<int>(SHOP_LIST::PARSNIP);


}

void Parsnip_Shop::Update()
{
}

void Parsnip_Shop::InventoryNewItem()
{
}

