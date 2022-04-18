#include "KaleSeeds_Shop.h"

KaleSeeds_Shop::KaleSeeds_Shop() 
{
}

KaleSeeds_Shop::~KaleSeeds_Shop() 
{
}

void KaleSeeds_Shop::Start()
{
	ShopItemListRenderer_ = CreateRenderer("KaleSeeds_Shop.bmp");
	ShopItemListRenderer_->CameraEffectOff();

	ShopItemListCollider_ = CreateCollision("Item", { 760, 73 });

	Index_ = static_cast<int>(SHOP_LIST::KALESEEDS);


}

void KaleSeeds_Shop::Update()
{
}

void KaleSeeds_Shop::InventoryNewItem()
{
}

