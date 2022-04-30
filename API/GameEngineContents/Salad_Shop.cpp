#include "Salad_Shop.h"
#include "Inventory.h"

Salad_Shop::Salad_Shop() 
{
}

Salad_Shop::~Salad_Shop() 
{
}

void Salad_Shop::Start()
{
	SetPosition({ 0.f,0.f });

	ShopItemListRenderer_ = CreateRenderer("Salad_Shop.bmp");
	ShopItemListRenderer_->CameraEffectOff();

	ShopItemListCollider_ = CreateCollision("Salad_Shop", { 760.f, 60.f });
	ShopItemListCollider_->SetPivot({ 0, +50.f / 2 });

	Index_ = static_cast<int>(SALOON_LIST::SALAD);

	BuyPrice_ = 60;
}

void Salad_Shop::Update()
{
}

void Salad_Shop::InventoryNewItem()
{
	//Inventory::MainInventory->NewItem<Bean_Seeds>();

}

bool Salad_Shop::MouseInItem()
{
	return (ShopItemListCollider_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));
}
