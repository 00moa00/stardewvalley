#include "Daffodil_Shop.h"

Daffodil_Shop::Daffodil_Shop() 
{
}

Daffodil_Shop::~Daffodil_Shop() 
{
}

void Daffodil_Shop::Start()
{
	ShopItemListRenderer_ = CreateRenderer("Daffodil_Shop.bmp");
	ShopItemListRenderer_->CameraEffectOff();

	ShopItemListCollider_ = CreateCollision("Item", { 760, 73 });

	Index_ = static_cast<int>(SHOP_LIST::DAFFODIL);


}

void Daffodil_Shop::Update()
{
}

void Daffodil_Shop::InventoryNewItem()
{
}

