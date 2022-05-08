#include "Beer.h"
#include "Inventory.h"

Beer* Beer::MainBear = nullptr;
Font* Beer::Font_ = nullptr;
ItemDataBox* Beer::MainItemDataBox = nullptr;

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

	ItemName_ = "Beer";

	ObjectType_ = OBJECTTYPE::DRINK;
	DrinkType_ = DRINKTYPE::SPEED_DOWN;

	SellPrice_ = 400;
	AddEnery_ = 50;
	AddHP_ = 22;
	ChangeSpeed_ = -1 * 100;
	ChangeTime_ = 30.f;

	ItemType_ = ITEMTYPE::ETC;

	if (Font_ == nullptr)
	{
		Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONT);
		Font_->ChangeWhiteColor();
		Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
	}

	if (MainItemDataBox == nullptr)
	{
		MainItemDataBox = GetLevel()->CreateActor<ItemDataBox>(static_cast<int>(PLAYLEVEL::DIALOGUEBOX));
		MainItemDataBox->SetData(ItemName_, " ", this->GetPosition());
	}


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
		if (MouseOver() && InMouse == false)
		{
			MainItemDataBox->ItemDataBoxOn();
			MainItemDataBox->SetData(ItemName_, "50 Energy /22 Health/ Speed -1", this->GetPosition());
		}
		else
		{
			MainItemDataBox->ItemDataBoxOff();
		}
		break;
	}
}

void Beer::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainBear = this;
	Font_ = Font_;
	MainItemDataBox = MainItemDataBox;

}

void Beer::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	++ItemCount_;
	MainItemDataBox->NextLevelOn();
	MainItemDataBox->FontNextLevelOn();
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
