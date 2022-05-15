#include "Parsnip_Seeds.h"
#include "Parsnip_Crops.h"
#include "Inventory.h"

Parsnip_Seeds* Parsnip_Seeds::MainParsnipSeeds = nullptr;
Font* Parsnip_Seeds::Font_ = nullptr;
ItemDataBox* Parsnip_Seeds::MainItemDataBox = nullptr;

Parsnip_Seeds::Parsnip_Seeds() 
{

}

Parsnip_Seeds::~Parsnip_Seeds() 
{

}

void Parsnip_Seeds::Start()
{
	ItemRenderer_ = CreateRenderer("springobjects.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::PARSNIP_SEEDS));
	ItemRenderer_->CameraEffectOff();

	ItemCollider_ = CreateCollision("Item", { 40, 40 });

	SeedType_ = SEEDTYPE::PARSNIP_SEED;
	ItemName_ = "Parsnip_Seeds";
	SellPrice_ = 35;

	ItemType_ = ITEMTYPE::ETC;
	ObjectType_ = OBJECTTYPE::SEED;

	if (Font_ == nullptr)
	{
		Font_ = GetLevel()->CreateActor<Font>(static_cast<int>(PLAYLEVEL::FONT));
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
	FileIndex_ = static_cast<size_t>(ITEM::PARSNIP_SEEDS);


}

void Parsnip_Seeds::Update()
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

void Parsnip_Seeds::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainParsnipSeeds = this;
	Font_ = Font_;
	MainItemDataBox = MainItemDataBox;
}

void Parsnip_Seeds::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Font_->NextLevelOn();
	MainItemDataBox->NextLevelOn();
	MainItemDataBox->FontNextLevelOn();
}

Crops* Parsnip_Seeds::CreateCrops()
{
	Crops* Crops_ = GetLevel()->CreateActor<Parsnip_Crops>(static_cast<int>(PLAYLEVEL::SEED));
	return Crops_;
}

void Parsnip_Seeds::AddItemCount()
{
	++ItemCount_;
	Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
}

void Parsnip_Seeds::SubItemCount()
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

void Parsnip_Seeds::SetItemCount(int _Count)
{
	ItemCount_ = _Count;
	Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
}

void Parsnip_Seeds::UpdateOff()
{
	this->Off();
	Font_->Off();
}

void Parsnip_Seeds::UpdateOn()
{
	this->On();
	Font_->On();
}

