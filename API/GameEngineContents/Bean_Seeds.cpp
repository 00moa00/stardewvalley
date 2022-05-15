#include "Bean_Seeds.h"
#include "Bean_Crops.h"
#include "Inventory.h"

Bean_Seeds* Bean_Seeds::MainBeanSeeds = nullptr;
Font* Bean_Seeds::Font_ = nullptr;
ItemDataBox* Bean_Seeds::MainItemDataBox = nullptr;

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

	ItemType_ = ITEMTYPE::ETC;
	ObjectType_ = OBJECTTYPE::SEED;

	SeedType_ = SEEDTYPE::BEAN_SEED;
	ItemName_ = "Bean_Seeds";
	SellPrice_ = 35;

	if (Font_ == nullptr)
	{
		Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONT);
		Font_->ChangeWhiteColor();
		Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
	}

	if (MainItemDataBox == nullptr)
	{
		MainItemDataBox = GetLevel()->CreateActor<ItemDataBox>(static_cast<int>(PLAYLEVEL::DIALOGUEBOX));
		//MainItemDataBox->SetData(ItemName_, " ", this->GetPosition());
	}

	//핸드 아이템용
	isPossibleHand_ = true;
	FileName_ = "springobjects.bmp";
	FileIndex_ = static_cast<size_t>(ITEM::BEAN_STARTER);

}

void Bean_Seeds::Update()
{
	switch (ItemState_)
	{
	case ITEM_STATE::INIT:
		Font_->SetPositionItem({ GetPosition() });
		if (MouseOver() && InMouse == false)
		{
			MainItemDataBox->ItemDataBoxOn();
			MainItemDataBox->SetData(ItemName_, "Takes 4 days /to mature.", this->GetPosition());
		}
		else
		{
			MainItemDataBox->ItemDataBoxOff();

		}

		break;
	}
}


void Bean_Seeds::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainBeanSeeds = this;
	MainItemDataBox = MainItemDataBox;
	Font_ = Font_;
}

void Bean_Seeds::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Font_->NextLevelOn();
	MainItemDataBox->NextLevelOn();
	MainItemDataBox->FontNextLevelOn();

}

Crops* Bean_Seeds::CreateCrops()
{
	Crops* Crops_ = GetLevel()->CreateActor<Bean_Crops>(static_cast<int>(PLAYLEVEL::SEED));
	return Crops_;
}

void Bean_Seeds::AddItemCount()
{
	++ItemCount_;
	Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
}

void Bean_Seeds::SubItemCount()
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

void Bean_Seeds::UpdateOff()
{
	this->Off();
	Font_->Off();
}

void Bean_Seeds::UpdateOn()
{
	this->On();
	Font_->On();
}
