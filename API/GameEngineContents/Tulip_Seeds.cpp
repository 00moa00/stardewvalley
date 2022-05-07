#include "Tulip_Seeds.h"
#include "Tulip_Crops.h"
#include "Inventory.h"

Tulip_Seeds* Tulip_Seeds::MainTulipSeeds = nullptr;
Font* Tulip_Seeds::Font_ = nullptr;

Tulip_Seeds::Tulip_Seeds() 
{
}

Tulip_Seeds::~Tulip_Seeds() 
{
}

void Tulip_Seeds::Start()
{
	ItemRenderer_ = CreateRenderer("springobjects.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::TULIP_BULB));
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
	FileIndex_ = static_cast<size_t>(ITEM::TULIP_BULB);

	SeedType_ = SEEDTYPE::TULIP_SEED;
	ItemName_ = "Tulip_Seeds";
	SellPrice_ = 35;
}

void Tulip_Seeds::Update()
{
	switch (ItemState_)
	{
	case ITEM_STATE::INIT:
		Font_->SetPositionItem({ GetPosition() });

		break;

	}
}

void Tulip_Seeds::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainTulipSeeds = this;
	Font_ = Font_;
}

void Tulip_Seeds::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Font_->NextLevelOn();
}

Crops* Tulip_Seeds::CreateCrops()
{
	Crops* Crops_ = GetLevel()->CreateActor<Tulip_Crops>(static_cast<int>(PLAYLEVEL::SEED));
	return Crops_;
}

void Tulip_Seeds::AddItemCount()
{
	++ItemCount_;
	Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
}

void Tulip_Seeds::SubItemCount()
{
	if (ItemCount_ == 1)
	{
		Player::MainPlayer->SetResetPlayerHandItem();
		Inventory::MainInventory->FindAndErasePlayerItemList(this->GetItemNameConstRef());
		Death();
	}
	else
	{
		--ItemCount_;
		Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
	}
}

void Tulip_Seeds::UpdateOff()
{
	this->Off();
	Font_->Off();
}

void Tulip_Seeds::UpdateOn()
{
	this->On();
	Font_->On();
}
