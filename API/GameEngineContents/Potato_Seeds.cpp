#include "Potato_Seeds.h"
#include "Inventory.h"

Potato_Seeds* Potato_Seeds::MainPotatoSeeds = nullptr;
Font* Potato_Seeds::Font_ = nullptr;


Potato_Seeds::Potato_Seeds() 
{
}

Potato_Seeds::~Potato_Seeds() 
{
}

void Potato_Seeds::Start()
{
	ItemRenderer_ = CreateRenderer("springobjects.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::POTATO_SEEDS));
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
	FileIndex_ = static_cast<size_t>(ITEM::POTATO_SEEDS);

	ItemType_ = ITEMTYPE::ITEM;
	ItemName_ = "Potato_Seeds";

	SellPrice_ = 35;

}

void Potato_Seeds::Update()
{
	switch (ItemState_)
	{
	case ITEM_STATE::INIT:
		Font_->SetPositionItem({ GetPosition() });

		break;

	}
}

void Potato_Seeds::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainPotatoSeeds = this;
	Font_ = Font_;
}

void Potato_Seeds::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Font_->NextLevelOn();
}

void Potato_Seeds::AddItemCount()
{
	++Count_;
	Font_->ChangeNumItemLeftSort(Count_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
}

void Potato_Seeds::SubItemCount()
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
