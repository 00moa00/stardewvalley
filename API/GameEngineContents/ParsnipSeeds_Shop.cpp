#include "ParsnipSeeds_Shop.h"
#include "Player.h"
#include "Parsnip_Seeds.h"

ParsnipSeeds_Shop* ParsnipSeeds_Shop::MainParsnipSeedsShop = nullptr;

ParsnipSeeds_Shop::ParsnipSeeds_Shop() 
{
}

ParsnipSeeds_Shop::~ParsnipSeeds_Shop() 
{
}

void ParsnipSeeds_Shop::Start()
{
	ShopItemListRenderer_ = CreateRenderer("ParsnipSeeds_Shop.bmp");
	ShopItemListRenderer_->CameraEffectOff();

	ShopItemListCollider_ = CreateCollision("ParsnipSeeds_Shop", { 760, 73 });

	Index_ = static_cast<int>(SHOP_LIST::PARSNIPSEEDS);

	BuyPrice_ = 20;

}

void ParsnipSeeds_Shop::Update()
{
}

void ParsnipSeeds_Shop::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainParsnipSeedsShop = this;
}

void ParsnipSeeds_Shop::InventoryNewItem()
{
	Player* MainPlayer = MainPlayer = GetLevel()->FindActor<Player>("MainPlayer");
	MainPlayer->GetInventroy()->NewItem<Parsnip_Seeds>();
}

bool ParsnipSeeds_Shop::MouseInItem()
{
	return (ShopItemListCollider_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));
}

