#include "FarmTotem.h"
#include "Inventory.h"

FarmTotem* FarmTotem::MainFarmTotem = nullptr;
Font* FarmTotem::Font_ = nullptr;

FarmTotem::FarmTotem()
{
}

FarmTotem::~FarmTotem()
{
}

void FarmTotem::Start()
{
	ItemRenderer_ = CreateRenderer("springobjects.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::WARP_TOTEM_FARM));
	ItemRenderer_->CameraEffectOff();

	ItemCollider_ = CreateCollision("Item", { 40, 40 });

	if (Font_ == nullptr)
	{
		Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONT);
		Font_->ChangeWhiteColor();
		Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
	}

	ItemName_ = "FarmTotem";
	ItemType_ = ITEMTYPE::FARMING;

	//핸드 아이템용
	isPossibleHand_ = true;
	FileName_ = "springobjects.bmp";
	FileIndex_ = static_cast<size_t>(ITEM::WARP_TOTEM_FARM);

	SellPrice_ = 35;
}

void FarmTotem::Update()
{
}

void FarmTotem::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainFarmTotem = this;
	Font_ = Font_;
}

void FarmTotem::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Font_->NextLevelOn();

}

void FarmTotem::AddItemCount()
{
}

void FarmTotem::SubItemCount()
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

void FarmTotem::UpdateOff()
{
	this->Off();
	Font_->Off();
}

void FarmTotem::UpdateOn()
{
	this->On();
	Font_->On();

}
