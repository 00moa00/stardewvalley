#include "Parsnip_Seeds.h"
#include "Inventory.h"

Parsnip_Seeds* Parsnip_Seeds::MainParsnipSeeds = nullptr;
Font* Parsnip_Seeds::Font_ = nullptr;



Parsnip_Seeds::Parsnip_Seeds() 
{

}

Parsnip_Seeds::~Parsnip_Seeds() 
{

}

void Parsnip_Seeds::Start()
{
	isPossibleHand_ = true;

	ItemName_ = "Parsnip_Seeds";
	FileName_ = "springobjects.bmp";
	FileIndex_ = static_cast<size_t>(ITEM::PARSNIP_SEEDS);

	if (Font_ == nullptr)
	{
		Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONT);
	}

	Font_->ChangeWhiteColor();
	Font_->ChangeNumItem(1);

	ItemRenderer_ = CreateRenderer(FileName_);
	ItemRenderer_->SetIndex(FileIndex_);
	ItemRenderer_->CameraEffectOff();

	ItemCollider_ = CreateCollision("Item", { 40, 40 });

	ItemType_ = ITEMTYPE::ITEM;

	SellPrice_ = 35;
}

void Parsnip_Seeds::Update()
{

	switch (ItemState_)
	{
	case ITEM_STATE::INIT:
		Font_->SetPositionItem({ GetPosition() });

		break;

	}
}

void Parsnip_Seeds::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainParsnipSeeds = this;
	Font_ = Font_;
}

void Parsnip_Seeds::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Font_->NextLevelOn();
}

void Parsnip_Seeds::SubItemCount()
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

