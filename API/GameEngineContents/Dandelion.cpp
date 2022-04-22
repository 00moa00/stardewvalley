#include "Dandelion.h"
#include "Inventory.h"

Dandelion* Dandelion::MainDandelion = nullptr;
Font* Dandelion::Font_ = nullptr;

Dandelion::Dandelion() 
{
}

Dandelion::~Dandelion() 
{
}

void Dandelion::Start()
{
	ItemRenderer_ = CreateRenderer("springobjects.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::DANDELION));
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
	FileIndex_ = static_cast<size_t>(ITEM::DANDELION);

	ItemType_ = ITEMTYPE::ITEM;
	ItemName_ = "Dandelion";

	SellPrice_ = 35;
}

void Dandelion::Update()
{
	switch (ItemState_)
	{
	case ITEM_STATE::INIT:
		Font_->SetPositionItem({ GetPosition() });

		break;
	}
}

void Dandelion::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainDandelion = this;
	Font_ = Font_;
}

void Dandelion::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Font_->NextLevelOn();
}

void Dandelion::AddItemCount()
{
	++Count_;
	Font_->ChangeNumItemLeftSort(Count_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
}

void Dandelion::SubItemCount()
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
