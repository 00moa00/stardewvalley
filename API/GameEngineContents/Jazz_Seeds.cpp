#include "Jazz_Seeds.h"
#include "Jazz_Crops.h"
#include "Inventory.h"

Jazz_Seeds* Jazz_Seeds::MainJazzSeeds = nullptr;
Font* Jazz_Seeds::Font_ = nullptr;

Jazz_Seeds::Jazz_Seeds() 
{
}

Jazz_Seeds::~Jazz_Seeds() 
{
}

void Jazz_Seeds::Start()
{

	ItemRenderer_ = CreateRenderer("springobjects.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::JAZZ_SEEDS));
	ItemRenderer_->CameraEffectOff();

	ItemCollider_ = CreateCollision("Item", { 40, 40 });

	if (Font_ == nullptr)
	{
		Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONT);
		Font_->ChangeWhiteColor();
		Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
	}
	ItemType_ = ITEMTYPE::ETC;
	ObjectType_ = OBJECTTYPE::SEED;

	//핸드 아이템용
	isPossibleHand_ = true;
	FileName_ = "springobjects.bmp";
	FileIndex_ = static_cast<size_t>(ITEM::JAZZ_SEEDS);

	SeedType_ = SEEDTYPE::JAZZ_SEED;
	ItemName_ = "Jazz_Seeds";
	SellPrice_ = 35;

}

void Jazz_Seeds::Update()
{
	switch (ItemState_)
	{
	case ITEM_STATE::INIT:
		Font_->SetPositionItem({ GetPosition() });

		break;

	}
}

void Jazz_Seeds::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainJazzSeeds = this;
	Font_ = Font_;
}

void Jazz_Seeds::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Font_->NextLevelOn();
}

Crops* Jazz_Seeds::CreateCrops()
{
	Crops* Crops_ = GetLevel()->CreateActor<Jazz_Crops>(static_cast<int>(PLAYLEVEL::SEED));
	return Crops_;
}

void Jazz_Seeds::AddItemCount()
{
	++ItemCount_;
	Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
}

void Jazz_Seeds::SubItemCount()
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

void Jazz_Seeds::UpdateOff()
{
	this->Off();
	Font_->Off();
}

void Jazz_Seeds::UpdateOn()
{
	this->On();
	Font_->On();
}
