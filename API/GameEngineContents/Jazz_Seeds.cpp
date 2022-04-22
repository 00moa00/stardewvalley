#include "Jazz_Seeds.h"
#include "Inventory.h"

Jazz_Seeds* Jazz_Seeds::MainJazzSeeds = nullptr;
Font* Jazz_Seeds::Font_ = nullptr;

Jazz_Seeds::Jazz_Seeds() 
{
}

Jazz_Seeds::~Jazz_Seeds() 
{
}

void Jazz_Seeds::Start()
{

	ItemRenderer_ = CreateRenderer("springobjects.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::JAZZ_SEEDS));
	ItemRenderer_->CameraEffectOff();

	ItemCollider_ = CreateCollision("Item", { 40, 40 });

	if (Font_ == nullptr)
	{
		Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONT);
		Font_->ChangeWhiteColor();
		Font_->ChangeNumItem(1);
	}

	//핸드 아이템용
	isPossibleHand_ = true;
	FileName_ = "springobjects.bmp";
	FileIndex_ = static_cast<size_t>(ITEM::JAZZ_SEEDS);

	ItemType_ = ITEMTYPE::ITEM;
	ItemName_ = "Jazz_Seeds";

	SellPrice_ = 35;


}

void Jazz_Seeds::Update()
{
	switch (ItemState_)
	{
	case ITEM_STATE::INIT:
		Font_->SetPositionItem({ GetPosition() });

		break;

	}
}

void Jazz_Seeds::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainJazzSeeds = this;
	Font_ = Font_;
}

void Jazz_Seeds::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Font_->NextLevelOn();
}

void Jazz_Seeds::AddItemCount()
{
	++Count_;
	Font_->ChangeNumItem(Count_);
}

void Jazz_Seeds::SubItemCount()
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
