#include "MineTotem.h"
#include "Inventory.h"

MineTotem* MineTotem::MainMineTotem = nullptr;
Font* MineTotem::Font_ = nullptr;
ItemDataBox* MineTotem::MainItemDataBox = nullptr;

MineTotem::MineTotem()
{
}

MineTotem::~MineTotem()
{
}

void MineTotem::Start()
{
	ItemRenderer_ = CreateRenderer("springobjects.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::WARP_TOTEM_MOUNTAINS));
	ItemRenderer_->CameraEffectOff();

	ItemCollider_ = CreateCollision("Item", { 40, 40 });

	SellPrice_ = 35;

	ItemName_ = "BackForestTotem";
	ItemType_ = ITEMTYPE::FARMING;

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
	FileIndex_ = static_cast<size_t>(ITEM::WARP_TOTEM_MOUNTAINS);

}

void MineTotem::Update()
{
	switch (ItemState_)
	{
	case ITEM_STATE::INIT:
		Font_->SetPositionItem({ GetPosition() });
		if (MouseOver() && InMouse == false)
		{
			MainItemDataBox->ItemDataBoxOn();
			MainItemDataBox->SetData("BackForest /Totem", "Warp directly /to BackForest. /Consumed on /use.", this->GetPosition());
		}
		else
		{
			MainItemDataBox->ItemDataBoxOff();

		}

		break;
	}
}

void MineTotem::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainMineTotem = this;
	Font_ = Font_;
	MainItemDataBox = MainItemDataBox;
}

void MineTotem::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Font_->NextLevelOn();
	MainItemDataBox->NextLevelOn();
	MainItemDataBox->FontNextLevelOn();
}

void MineTotem::AddItemCount()
{
	++ItemCount_;
	Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
}

void MineTotem::SubItemCount()
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

void MineTotem::UpdateOff()
{
	this->Off();
	Font_->Off();
}

void MineTotem::UpdateOn()
{
	this->On();
	Font_->On();

}

void MineTotem::SetItemCount(int _Count)
{
	ItemCount_ = _Count;
	Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
}
