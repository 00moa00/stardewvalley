#include "Beer.h"
#include "Inventory.h"

Beer* Beer::MainBear = nullptr;
Font* Beer::Font_ = nullptr;

Beer::Beer() 
{
}

Beer::~Beer() 
{
}

void Beer::Start()
{
	ItemRenderer_ = CreateRenderer("springobjects.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::BEER));
	ItemRenderer_->CameraEffectOff();

	ItemCollider_ = CreateCollision("Item", { 40, 40 });

	if (Font_ == nullptr)
	{
		Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONT);
		Font_->ChangeWhiteColor();
		Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
	}


	ItemName_ = "Beer";

	ObjectType_ = OBJECTTYPE::DRINK;
	DrinkType_ = DRINKTYPE::SPEED_DOWN;

	SellPrice_ = 400;
	AddEnery_ = 50;
	AddHP_ = 22;
	ChangeSpeed_ = -1 * 100;
	ChangeTime_ = 30.f;

	ItemType_ = ITEMTYPE::ETC;

	//핸드 아이템용
	isPossibleHand_ = true;
	FileName_ = "springobjects.bmp";
	FileIndex_ = static_cast<size_t>(ITEM::BEER);
}

void Beer::Update()
{
	switch (ItemState_)
	{
	case ITEM_STATE::INIT:
		Font_->SetPositionItem({ GetPosition() });

		break;
	}
}

void Beer::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainBear = this;
	Font_ = Font_;
}

void Beer::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	++ItemCount_;
	Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
}

void Beer::AddItemCount()
{
	++ItemCount_;
	Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
}

void Beer::SubItemCount()
{
	if (ItemCount_ == 1)
	{
		ItemCount_ = 0;
		Player::MainPlayer->SetResetPlayerHandItem();
		Inventory::MainInventory->FindAndErasePlayerItemList(this->GetItemNameConstRef());
		Font_ = nullptr;
		this->Death();
	}
	else
	{
		--ItemCount_;
		Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
	}
}

void Beer::UpdateOff()
{
	this->Off();
	Font_->Off();
}

void Beer::UpdateOn()
{
	this->On();
	Font_->On();
}
