#include "CauliflowerSeeds_Shop.h"
#include "Cauliflower_Seeds.h"
#include "Player.h"

CauliflowerSeeds_Shop::CauliflowerSeeds_Shop() 
{
}

CauliflowerSeeds_Shop::~CauliflowerSeeds_Shop() 
{
}

void CauliflowerSeeds_Shop::Start()
{
	SetPosition({ 0.f,0.f });

	ShopItemListRenderer_ = CreateRenderer("CauliflowerSeeds_Shop.bmp");
	ShopItemListRenderer_->CameraEffectOff();

	ShopItemListCollider_ = CreateCollision("CauliflowerSeeds_Shop", { 760.f, 60.f });
	ShopItemListCollider_->SetPivot({ 0, +60.f / 2 });

	Index_ = static_cast<int>(SHOP_LIST::CAULIFLOWERSEEDS);

	BuyPrice_ = 80;
}


void CauliflowerSeeds_Shop::Update()
{
}

void CauliflowerSeeds_Shop::InventoryNewItem()
{
	Player::MainPlayer->GetInventroy()->NewItem<Cauliflower_Seeds>();

}

bool CauliflowerSeeds_Shop::MouseInItem()
{
	return (ShopItemListCollider_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));
}

