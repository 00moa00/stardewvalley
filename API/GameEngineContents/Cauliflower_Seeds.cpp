#include "Cauliflower_Seeds.h"
#include "Inventory.h"

Cauliflower_Seeds* Cauliflower_Seeds:: MainCauliflowerSeeds = nullptr;
Font* Cauliflower_Seeds::Font_ = nullptr;

Cauliflower_Seeds::Cauliflower_Seeds() 
{
}

Cauliflower_Seeds::~Cauliflower_Seeds() 
{
}

void Cauliflower_Seeds::Start()
{
	ItemRenderer_ = CreateRenderer("springobjects.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::CAULIFLOWER_SEEDS));
	ItemRenderer_->CameraEffectOff();

	ItemCollider_ = CreateCollision("Item", { 40, 40 });

	if (Font_ == nullptr)
	{
		Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONT);
		Font_->ChangeWhiteColor();
		Font_->ChangeNumItemLeftSort( 1, {GetPosition().x + 11.f ,GetPosition().y + 11.f});
	}

	//핸드 아이템용
	isPossibleHand_ = true;
	FileName_ = "springobjects.bmp";
	FileIndex_ = static_cast<size_t>(ITEM::CAULIFLOWER_SEEDS);

	ItemType_ = ITEMTYPE::ITEM;
	ItemName_ = "Cauliflower_Seeds";

	SellPrice_ = 35;
}

void Cauliflower_Seeds::Update()
{
	switch (ItemState_)
	{
	case ITEM_STATE::INIT:
		Font_->SetPositionItem({ GetPosition() });

		break;
	}

}

void Cauliflower_Seeds::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainCauliflowerSeeds = this;
	Font_ = Font_;
}

void Cauliflower_Seeds::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Font_->NextLevelOn();
}

void Cauliflower_Seeds::AddItemCount()
{
	++Count_;
	Font_->ChangeNumItemLeftSort(Count_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
}

void Cauliflower_Seeds::SubItemCount()
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
