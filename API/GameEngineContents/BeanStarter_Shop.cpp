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

	BuyPrice_ = 60;
}


void BeanStarter_Shop::Update()
{
}

void BeanStarter_Shop::InventoryNewItem()
{
}

bool BeanStarter_Shop::MouseInItem()
{
	return (ShopItemListCollider_->CollisionResult("BeanStarter_Shop", ColList, CollisionType::Rect, CollisionType::Rect));
}

