#include "BeanStarter_Shop.h"

BeanStarter_Shop::BeanStarter_Shop() 
{
}

BeanStarter_Shop::~BeanStarter_Shop() 
{
}

void BeanStarter_Shop::Start()
{
	ShopItemListRenderer_ = CreateRenderer("BeanStarter_Shop.bmp");
	ShopItemListRenderer_->CameraEffectOff();

	ShopItemListCollider_ = CreateCollision("Item", { 760, 73 });

	Index_ = static_cast<int>(SHOP_LIST::BEANSTARTER);

}

void BeanStarter_Shop::Update()
{
}

void BeanStarter_Shop::InventoryNewItem()
{
}

