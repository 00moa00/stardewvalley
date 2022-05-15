#include "Cauliflower_Seeds.h"
#include "Cauliflower_Crops.h"
#include "Inventory.h"

Cauliflower_Seeds* Cauliflower_Seeds:: MainCauliflowerSeeds = nullptr;
Font* Cauliflower_Seeds::Font_ = nullptr;
ItemDataBox* Cauliflower_Seeds::MainItemDataBox = nullptr;

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

	SeedType_ = SEEDTYPE::CAULIFLOWER_SEED;
	ItemName_ = "Cauliflower_Seeds";
	SellPrice_ = 35;

	ItemType_ = ITEMTYPE::ETC;
	ObjectType_ = OBJECTTYPE::SEED;
	if (Font_ == nullptr)
	{
		Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONT);
		Font_->ChangeWhiteColor();
		Font_->ChangeNumItemLeftSort( 1, {GetPosition().x + 11.f ,GetPosition().y + 11.f});
	}

	if (MainItemDataBox == nullptr)
	{
		MainItemDataBox = GetLevel()->CreateActor<ItemDataBox>(static_cast<int>(PLAYLEVEL::DIALOGUEBOX));
		//MainItemDataBox->SetData(ItemName_, " ", this->GetPosition());
	}

	//핸드 아이템용
	isPossibleHand_ = true;
	FileName_ = "springobjects.bmp";
	FileIndex_ = static_cast<size_t>(ITEM::CAULIFLOWER_SEEDS);

}

void Cauliflower_Seeds::Update()
{
	switch (ItemState_)
	{
	case ITEM_STATE::INIT:
		Font_->SetPositionItem({ GetPosition() });
		if (MouseOver() && InMouse == false)
		{
			MainItemDataBox->ItemDataBoxOn();
			MainItemDataBox->SetData(ItemName_, "Takes 12 days /to mature.", this->GetPosition());
		}
		else
		{
			MainItemDataBox->ItemDataBoxOff();

		}

		break;
	}

}

void Cauliflower_Seeds::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainCauliflowerSeeds = this;
	Font_ = Font_;
	MainItemDataBox = MainItemDataBox;

}

void Cauliflower_Seeds::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Font_->NextLevelOn();
	MainItemDataBox->NextLevelOn();
	MainItemDataBox->FontNextLevelOn();

}

Crops* Cauliflower_Seeds::CreateCrops()
{
	Crops* Crops_ = GetLevel()->CreateActor<Cauliflower_Crops>(static_cast<int>(PLAYLEVEL::SEED));
	return Crops_;
}

void Cauliflower_Seeds::AddItemCount()
{
	++ItemCount_;
	Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
}

void Cauliflower_Seeds::SubItemCount()
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

void Cauliflower_Seeds::SetItemCount(int _Count)
{
	ItemCount_ = _Count;
	Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
}

void Cauliflower_Seeds::UpdateOff()
{
	this->Off();
	Font_->Off();
}

void Cauliflower_Seeds::UpdateOn()
{
	this->On();
	Font_->On();
}
