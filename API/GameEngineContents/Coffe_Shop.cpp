#include "Coffe_Shop.h"

Coffe_Shop::Coffe_Shop() 
{
}

Coffe_Shop::~Coffe_Shop() 
{
}

void Coffe_Shop::Start()
{
	SetPosition({ 0.f,0.f });

	ShopItemListRenderer_ = CreateRenderer("Coffe_Shop.bmp");
	ShopItemListRenderer_->CameraEffectOff();

	ShopItemListCollider_ = CreateCollision("Coffe_Shop", { 760.f, 60.f });
	ShopItemListCollider_->SetPivot({ 0, +50.f / 2 });

	Index_ = static_cast<int>(SALOON_LIST::COFFE);

	BuyPrice_ = 60;
}

void Coffe_Shop::Update()
{
}

void Coffe_Shop::InventoryNewItem()
{
	//Inventory::MainInventory->NewItem<Bean_Seeds>();
}

bool Coffe_Shop::MouseInItem()
{
	return (ShopItemListCollider_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));
}
