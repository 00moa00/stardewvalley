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

	ItemCollider_ = CreateCollision("Item", { 40.f , 40.f });


	if (Font_ == nullptr)
	{
		Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONT);
	}

	Font_->ChangeWhiteColor();
	Font_->ChangeNumItemLeftSort(Count_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });


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
void DropStone::AddItemCount()
{
	++Count_;
	Font_->ChangeNumItemLeftSort(Count_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
}

void DropStone::SubItemCount()
{
	if (Count_ == 1)
	{
		Count_ = 0;
		Player::MainPlayer->SetResetPlayerHandItem();
		Inventory::MainInventory->FindAndErasePlayerItemList(this->GetItemNameConstRef());
		Font_ = nullptr;
		this->Death();
	}
	else
	{
		--Count_;
		Font_->ChangeNumItemLeftSort(Count_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
	}

}

void DropStone::UpdateOff()
{
	this->Off();
	Font_->Off();
}

void DropStone::UpdateOn()
{
	this->On();
	Font_->On();
}
