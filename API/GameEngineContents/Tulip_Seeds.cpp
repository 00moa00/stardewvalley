#include "Tulip_Seeds.h"
#include "Inventory.h"

Tulip_Seeds* Tulip_Seeds::MainTulipSeeds = nullptr;
Font* Tulip_Seeds::Font_ = nullptr;

Tulip_Seeds::Tulip_Seeds() 
{
}

Tulip_Seeds::~Tulip_Seeds() 
{
}

void Tulip_Seeds::Start()
{
	ItemRenderer_ = CreateRenderer("springobjects.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::TULIP_BULB));
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
	FileIndex_ = static_cast<size_t>(ITEM::TULIP_BULB);

	ItemType_ = ITEMTYPE::ITEM;
	ItemName_ = "Tulip_Seeds";

	SellPrice_ = 35;
}

void Tulip_Seeds::Update()
{
	switch (ItemState_)
	{
	case ITEM_STATE::INIT:
		Font_->SetPositionItem({ GetPosition() });

		break;

	}
}

void Tulip_Seeds::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainTulipSeeds = this;
	Font_ = Font_;
}

void Tulip_Seeds::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Font_->NextLevelOn();
}

void Tulip_Seeds::AddItemCount()
{
	++Count_;
	Font_->ChangeNumItemLeftSort(Count_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
}

void Tulip_Seeds::SubItemCount()
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
