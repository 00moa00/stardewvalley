#include "DropStone.h"
#include "Player.h"

DropStone* DropStone::MainDropStone = nullptr;
Font* DropStone::Font_;

DropStone::DropStone() 

{
}

DropStone::~DropStone() 
{
}

void DropStone::Start()
{
	ItemSpeed_.x = 1.f;
	ItemSpeed_.y = 5.f;
	Gravity_.y = 0.1f;

	ItemRenderer_ = CreateRenderer("springobjects.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::MINI_STONE));
	ItemRenderer_->CameraEffectOn();

	MapItemCollider_ = CreateCollision("MapObject", { 20, 10 });
	ItemCollider_ = CreateCollision("Item", { 40.f , 40.f });


	if (Font_ == nullptr)
	{
		Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONT);
	}

	Font_->ChangeWhiteColor();
	Font_->ChangeNumItem(1);


	ItemType_ = ITEMTYPE::ITEM;
	ItemName_ = "DropStone";

}

void DropStone::Update()
{

	MoveToPlayer();

	if (isItemDeath_ == true)
	{
		Player* MainPlayer = GetLevel()->FindActor<Player>("MainPlayer");
		MainPlayer->GetInventroy()->NewItem<DropStone>();
	}

	switch (ItemState_)
	{
	case ITEM_STATE::INIT:
		Font_->SetPositionItem({ GetPosition() });

		break;

	}

}
void DropStone::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainDropStone = this;
	Font_ = Font_;

}
void DropStone::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Font_->NextLevelOn();

}
void DropStone::SubItemCount()
{
	if (Count_ == 1)
	{
		Player::MainPlayer->SetResetPlayerHandItem();
		Inventory::MainInventory->FindAndErasePlayerItemList(this->GetItemNameConstRef());
		Death();
	}
	else
	{
		--Count_;
		Font_->ChangeNumItem(Count_);
	}

}