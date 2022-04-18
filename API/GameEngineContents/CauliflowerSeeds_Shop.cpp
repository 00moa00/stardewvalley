#include "CauliflowerSeeds_Shop.h"

CauliflowerSeeds_Shop::CauliflowerSeeds_Shop() 
{
}

CauliflowerSeeds_Shop::~CauliflowerSeeds_Shop() 
{
}

void CauliflowerSeeds_Shop::Start()
{
	ShopItemListRenderer_ = CreateRenderer("CauliflowerSeeds_Shop.bmp");
	ShopItemListRenderer_->CameraEffectOff();

	ShopItemListCollider_ = CreateCollision("CauliflowerSeeds_Shop", { 760, 73 });

	Index_ = static_cast<int>(SHOP_LIST::CAULIFLOWERSEEDS);

	BuyPrice_ = 80;
}


void CauliflowerSeeds_Shop::Update()
{
}

void CauliflowerSeeds_Shop::InventoryNewItem()
{
}

bool CauliflowerSeeds_Shop::MouseInItem()
{
	return (ShopItemListCollider_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));
}

