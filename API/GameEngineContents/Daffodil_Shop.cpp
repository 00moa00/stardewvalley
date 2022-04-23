#include "Daffodil_Shop.h"
#include "Daffodil.h"
#include "Player.h"

Daffodil_Shop::Daffodil_Shop() 
{
}

Daffodil_Shop::~Daffodil_Shop() 
{
}

void Daffodil_Shop::Start()
{
	SetPosition({ 0.f,0.f });

	ShopItemListRenderer_ = CreateRenderer("Daffodil_Shop.bmp");
	ShopItemListRenderer_->CameraEffectOff();

	ShopItemListCollider_ = CreateCollision("Daffodil_Shop", { 760.f, 73.f });
	ShopItemListCollider_->SetPivot({ 0, +50.f / 2 });

	Index_ = static_cast<int>(SHOP_LIST::DAFFODIL);

	BuyPrice_ = 35;
}

void Daffodil_Shop::Update()
{
}

void Daffodil_Shop::InventoryNewItem()
{
	Player::MainPlayer->GetInventroy()->NewItem<Daffodil>();

}

bool Daffodil_Shop::MouseInItem()
{
	return (ShopItemListCollider_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));
}

