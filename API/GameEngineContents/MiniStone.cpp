#include "MiniStone.h"
#include "Player.h"

MiniStone* MiniStone::MainMiniStone = nullptr;
Font* MiniStone::Font_;

MiniStone::MiniStone() 

{
}

MiniStone::~MiniStone() 
{
}

void MiniStone::Start()
{
	ItemSpeed_.x = 1.f;
	ItemSpeed_.y = 5.f;
	Gravity_.y = 0.1f;

	ItemRenderer_ = CreateRenderer("springobjects.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::MINI_STONE));
	ItemRenderer_->CameraEffectOn();

	MapItemCollider_ = CreateCollision("MapObject", { 20, 10 });
	ItemCollider_ = CreateCollision("Item", { 40, 40 });


	if (Font_ == nullptr)
	{
		Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONT);
	}

	Font_->ChangeWhiteColor();
	Font_->ChangeNumItem(1);


	ItemType_ = ITEMTYPE::ITEM;
	ItemName_ = "MiniStone";


}

void MiniStone::Update()
{

	MoveToPlayer();

	if (isDeath_ == true)
	{
		Player* MainPlayer = GetLevel()->FindActor<Player>("MainPlayer");
		MainPlayer->GetInventroy()->NewItem<MiniStone>();
	}

	switch (ItemState_)
	{
	case ITEM_STATE::INIT:
		Font_->SetPositionItem({ GetPosition() });

		break;

	}

}
void MiniStone::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainMiniStone = this;
	Font_ = Font_;

}
void MiniStone::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Font_->NextLevelOn();

}
void MiniStone::SubItemCount()
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