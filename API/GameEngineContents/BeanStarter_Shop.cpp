#include "BeanStarter_Shop.h"
#include "Bean_Seeds.h"
#include "Inventory.h"

BeanStarter_Shop::BeanStarter_Shop() 
{
}

BeanStarter_Shop::~BeanStarter_Shop() 
{
}

void BeanStarter_Shop::Start()
{
	SetPosition({ 0.f,0.f });
	
	ShopItemListRenderer_ = CreateRenderer("BeanStarter_Shop.bmp");
	ShopItemListRenderer_->CameraEffectOff();

	ShopItemListCollider_ = CreateCollision("BeanStarter_Shop", { 760.f, 60.f });
	ShopItemListCollider_->SetPivot({ 0, +50.f / 2 });

	Index_ = static_cast<int>(SHOP_LIST::BEANSTARTER);

	BuyPrice_ = 60;
}


void BeanStarter_Shop::Update()
{
}

void BeanStarter_Shop::InventoryNewItem()
{
	Inventory::MainInventory->NewItem<Bean_Seeds>();

}

bool BeanStarter_Shop::MouseInItem()
{
	return (ShopItemListCollider_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));
}

