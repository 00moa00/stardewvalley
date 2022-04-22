#include "Kale_Seeds.h"
#include "Inventory.h"

Kale_Seeds* Kale_Seeds::MainKaleSeeds = nullptr;
Font* Kale_Seeds::Font_ = nullptr;

Kale_Seeds::Kale_Seeds() 
{
}

Kale_Seeds::~Kale_Seeds() 
{
}

void Kale_Seeds::Start()
{
	ItemRenderer_ = CreateRenderer("springobjects.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::KALE_SEEDS));
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
	FileIndex_ = static_cast<size_t>(ITEM::KALE_SEEDS);

	ItemType_ = ITEMTYPE::ITEM;
	ItemName_ = "KALE_SEEDS";

	SellPrice_ = 35;
}

void Kale_Seeds::Update()
{

	switch (ItemState_)
	{
	case ITEM_STATE::INIT:
		Font_->SetPositionItem({ GetPosition() });

		break;
	}
}

void Kale_Seeds::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainKaleSeeds = this;
	Font_ = Font_;
}

void Kale_Seeds::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Font_->NextLevelOn();
}

void Kale_Seeds::AddItemCount()
{
	++Count_;
	Font_->ChangeNumItem(Count_);
}

void Kale_Seeds::SubItemCount()
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
