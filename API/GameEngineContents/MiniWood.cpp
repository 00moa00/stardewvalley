#include "MiniWood.h"
#include "Player.h"

MiniWood::MiniWood() 
{
}

MiniWood::~MiniWood() 
{
}

void MiniWood::Start()
{
	ItemSpeed_.x = 1.f;
	ItemSpeed_.y = 5.f;
	Gravity_.y = 0.1f;

	ItemRenderer_ = CreateRenderer("springobjects.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::MINI_WOOD));
	ItemRenderer_->CameraEffectOn();

	ItemCollider_ = CreateCollision("MapObject", { 20, 20 });

	Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONT);
	Font_->ChangeWhiteColor();

	Font_->ChangeNumItem(1);


	ItemType_ = ITEMTYPE::ITEM;

	Name_ = "MiniWood";
}

void MiniWood::Update()
{
	MoveToPlayer();

}

