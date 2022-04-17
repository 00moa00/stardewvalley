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

	ShopItemListCollider_ = CreateCollision("Item", { 760, 73 });

	Index_ = static_cast<int>(SHOP_LIST::CAULIFLOWERSEEDS);

}

void CauliflowerSeeds_Shop::Update()
{
}

