#include "Potato.h"
#include "Inventory.h"

Potato* Potato::MainPotato = nullptr;
Font* Potato::Font_ = nullptr;

Potato::Potato() 
{
}

Potato::~Potato() 
{
}

void Potato::Start()
{
	ItemRenderer_ = CreateRenderer("springobjects.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::POTATO));
	ItemRenderer_->CameraEffectOff();

	ItemCollider_ = CreateCollision("Item", { 40, 40 });

	if (Font_ == nullptr)
	{
		Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONT);
		Font_->ChangeWhiteColor();
		Font_->ChangeNumItemLeftSort(Count_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
	}

	//핸드 아이템용
	isPossibleHand_ = true;
	FileName_ = "springobjects.bmp";
	FileIndex_ = static_cast<size_t>(ITEM::POTATO);

	ItemType_ = ITEMTYPE::ITEM;
	ItemName_ = "Potato";

	SellPrice_ = 35;
}

void Potato::Update()
{
	switch (ItemState_)
	{
	case ITEM_STATE::INIT:
		Font_->SetPositionItem({ GetPosition() });

		break;
	}

}

void Potato::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainPotato = this;
	Font_ = Font_;
}

void Potato::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Font_->NextLevelOn();
}

void Potato::AddItemCount()
{
	++Count_;
	Font_->ChangeNumItemLeftSort(Count_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
}

void Potato::SubItemCount()
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
		Font_->ChangeNumItemLeftSort(Count_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
	}
}
