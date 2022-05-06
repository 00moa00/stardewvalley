#include "Cauliflower_Seeds.h"
#include "Cauliflower_Crops.h"
#include "Inventory.h"

Cauliflower_Seeds* Cauliflower_Seeds:: MainCauliflowerSeeds = nullptr;
Font* Cauliflower_Seeds::Font_ = nullptr;

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

	if (Font_ == nullptr)
	{
		Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONT);
		Font_->ChangeWhiteColor();
		Font_->ChangeNumItemLeftSort( 1, {GetPosition().x + 11.f ,GetPosition().y + 11.f});
	}
	ItemType_ = ITEMTYPE::ETC;

	//핸드 아이템용
	isPossibleHand_ = true;
	FileName_ = "springobjects.bmp";
	FileIndex_ = static_cast<size_t>(ITEM::CAULIFLOWER_SEEDS);

	SeedType_ = SEEDTYPE::CAULIFLOWER_SEED;
	ItemName_ = "Cauliflower_Seeds";
	SellPrice_ = 35;
}

void Cauliflower_Seeds::Update()
{
	switch (ItemState_)
	{
	case ITEM_STATE::INIT:
		Font_->SetPositionItem({ GetPosition() });

		break;
	}

}

void Cauliflower_Seeds::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainCauliflowerSeeds = this;
	Font_ = Font_;
}

void Cauliflower_Seeds::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Font_->NextLevelOn();
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
