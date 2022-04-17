#include "TulipBulb_Shop.h"

TulipBulb_Shop::TulipBulb_Shop() 
{
}

TulipBulb_Shop::~TulipBulb_Shop() 
{
}

void TulipBulb_Shop::Start()
{


	ShopItemListRenderer_ = CreateRenderer("TulipBulb_Shop.bmp");
	ShopItemListRenderer_->CameraEffectOff();

	ShopItemListCollider_ = CreateCollision("Item", { 760, 73 });

	Index_ = static_cast<int>(SHOP_LIST::TULIPBULB);

}

void TulipBulb_Shop::Update()
{
}

