#include "Kale.h"
#include "Inventory.h"

Kale* Kale::MainKale = nullptr;
Font* Kale::Font_ = nullptr;

Kale::Kale() 
{
}

Kale::~Kale() 
{
}

void Kale::Start()
{
	ItemRenderer_ = CreateRenderer("springobjects.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::KALE));
	ItemRenderer_->CameraEffectOff();

	ItemCollider_ = CreateCollision("Item", { 40, 40 });

	if (Font_ == nullptr)
	{
		Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONT);
		Font_->ChangeWhiteColor();
		Font_->ChangeNumItemLeftSort(Count_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
	}

	ItemName_ = "Kale";

	//핸드 아이템용
	isPossibleHand_ = true;
	FileName_ = "springobjects.bmp";
	FileIndex_ = static_cast<size_t>(ITEM::KALE);

	SellPrice_ = 35;
}

void Kale::Update()
{
	MoveToPlayer();

	if (isItemDeath_ == true)
	{
		Player* MainPlayer = GetLevel()->FindActor<Player>("MainPlayer");
		MainPlayer->GetInventroy()->NewItem<Kale>();
	}

	switch (ItemState_)
	{
	case ITEM_STATE::INIT:
		Font_->SetPositionItem({ GetPosition() });

		break;

	}
}

void Kale::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainKale = this;
	Font_ = Font_;
}

void Kale::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Font_->NextLevelOn();

}

void Kale::AddItemCount()
{
	++Count_;
	Font_->ChangeNumItemLeftSort(Count_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
}

void Kale::SubItemCount()
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
