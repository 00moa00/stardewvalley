#include "FarmTotem.h"
#include "Inventory.h"

FarmTotem* FarmTotem::MainFarmTotem = nullptr;
Font* FarmTotem::Font_ = nullptr;
ItemDataBox* FarmTotem::MainItemDataBox = nullptr;

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

	ItemName_ = "FarmTotem";
	ItemType_ = ITEMTYPE::FARMING;

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
	FileIndex_ = static_cast<size_t>(ITEM::WARP_TOTEM_FARM);


}

void FarmTotem::Update()
{
	switch (ItemState_)
	{
	case ITEM_STATE::INIT:
		Font_->SetPositionItem({ GetPosition() });
		if (MouseOver() && InMouse == false)
		{
			MainItemDataBox->ItemDataBoxOn();
			MainItemDataBox->SetData(ItemName_, "Warp directly /to your house. /Consumed on /use.", this->GetPosition());
		}
		else
		{
			MainItemDataBox->ItemDataBoxOff();

		}

		break;
	}

}

void FarmTotem::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainFarmTotem = this;
	Font_ = Font_;
	MainItemDataBox = MainItemDataBox;
}

void FarmTotem::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Font_->NextLevelOn();
	MainItemDataBox->NextLevelOn();
	MainItemDataBox->FontNextLevelOn();
}

void FarmTotem::AddItemCount()
{
	++ItemCount_;
	Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
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

void FarmTotem::SetItemCount(int _Count)
{
	ItemCount_ = _Count;
	Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
}
