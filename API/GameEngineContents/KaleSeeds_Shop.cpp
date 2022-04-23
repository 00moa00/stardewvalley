#include "KaleSeeds_Shop.h"
#include "Kale_Seeds.h"
#include "Player.h"

KaleSeeds_Shop::KaleSeeds_Shop() 
{
}

KaleSeeds_Shop::~KaleSeeds_Shop() 
{
}

void KaleSeeds_Shop::Start()
{
	SetPosition({ 0.f,0.f });

	ShopItemListRenderer_ = CreateRenderer("KaleSeeds_Shop.bmp");
	ShopItemListRenderer_->CameraEffectOff();

	ShopItemListCollider_ = CreateCollision("KaleSeeds_Shop", { 760.f, 60.f });
	ShopItemListCollider_->SetPivot({ 0, +50.f / 2 });

	Index_ = static_cast<int>(SHOP_LIST::KALESEEDS);

	BuyPrice_ = 70;
}


void KaleSeeds_Shop::Update()
{
}

void KaleSeeds_Shop::InventoryNewItem()
{
	Player::MainPlayer->GetInventroy()->NewItem<Kale_Seeds>();
}

bool KaleSeeds_Shop::MouseInItem()
{
	return (ShopItemListCollider_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));
}

