#include "Bean_Seeds.h"
#include "Inventory.h"

Bean_Seeds* Bean_Seeds::MainBeanSeeds = nullptr;
Font* Bean_Seeds::Font_ = nullptr;

Bean_Seeds::Bean_Seeds() 
{
}

Bean_Seeds::~Bean_Seeds() 
{
}

void Bean_Seeds::Start()
{
	ItemRenderer_ = CreateRenderer("springobjects.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::BEAN_STARTER));
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
	FileIndex_ = static_cast<size_t>(ITEM::BEAN_STARTER);

	ItemType_ = ITEMTYPE::ITEM;
	ItemName_ = "Bean_Seeds";

	SellPrice_ = 35;
}

void Bean_Seeds::Update()
{
	switch (ItemState_)
	{
	case ITEM_STATE::INIT:
		Font_->SetPositionItem({ GetPosition() });

		break;
	}
}

void Bean_Seeds::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainBeanSeeds = this;
	Font_ = Font_;
}

void Bean_Seeds::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Font_->NextLevelOn();
}

void Bean_Seeds::AddItemCount()
{
	++Count_;
	Font_->ChangeNumItemLeftSort(Count_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
}

void Bean_Seeds::SubItemCount()
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
