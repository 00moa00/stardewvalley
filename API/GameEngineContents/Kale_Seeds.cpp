#include "Kale_Seeds.h"
#include "Kale_Crops.h"
#include "Inventory.h"

Kale_Seeds* Kale_Seeds::MainKaleSeeds = nullptr;
Font* Kale_Seeds::Font_ = nullptr;
ItemDataBox* Kale_Seeds::MainItemDataBox = nullptr;

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
	SeedType_ = SEEDTYPE::KALE_SEED;
	ItemName_ = "KALE_SEEDS";
	SellPrice_ = 35;

	ItemType_ = ITEMTYPE::ETC;
	ObjectType_ = OBJECTTYPE::SEED;


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
	FileIndex_ = static_cast<size_t>(ITEM::KALE_SEEDS);


}

void Kale_Seeds::Update()
{

	switch (ItemState_)
	{
	case ITEM_STATE::INIT:
		Font_->SetPositionItem({ GetPosition() });
		if (MouseOver() && InMouse == false)
		{
			MainItemDataBox->ItemDataBoxOn();
			MainItemDataBox->SetData(ItemName_, "Takes 6 days /to mature.", this->GetPosition());
		}
		else
		{
			MainItemDataBox->ItemDataBoxOff();

		}

		break;
	}
}

void Kale_Seeds::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainKaleSeeds = this;
	Font_ = Font_;
	MainItemDataBox = MainItemDataBox;
}

void Kale_Seeds::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Font_->NextLevelOn();
	MainItemDataBox->NextLevelOn();
	MainItemDataBox->FontNextLevelOn();

}

Crops* Kale_Seeds::CreateCrops()
{
	Crops* Crops_ = GetLevel()->CreateActor<Kale_Crops>(static_cast<int>(PLAYLEVEL::SEED));
	return Crops_;
}

void Kale_Seeds::AddItemCount()
{
	++ItemCount_;
	Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
}

void Kale_Seeds::SubItemCount()
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

void Kale_Seeds::UpdateOff()
{
	this->Off();
	Font_->Off();
}

void Kale_Seeds::UpdateOn()
{
	this->On();
	Font_->On();
}
