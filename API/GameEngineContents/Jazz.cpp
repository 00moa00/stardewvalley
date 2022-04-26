#include "Jazz.h"
#include "Inventory.h"

Jazz* Jazz::MainJazz = nullptr;
Font* Jazz::Font_ = nullptr;

Jazz::Jazz() 
{
}

Jazz::~Jazz() 
{
}

void Jazz::Start()
{
	ItemRenderer_ = CreateRenderer("springobjects.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::BLUE_JAZZ));
	ItemRenderer_->CameraEffectOff();

	ItemCollider_ = CreateCollision("Item", { 40, 40 });

	if (Font_ == nullptr)
	{
		Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONT);
		Font_->ChangeWhiteColor();
		Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
	}

	ItemName_ = "Jazz";

	//핸드 아이템용
	isPossibleHand_ = true;
	FileName_ = "springobjects.bmp";
	FileIndex_ = static_cast<size_t>(ITEM::BLUE_JAZZ);

	SellPrice_ = 35;
}

void Jazz::Update()
{
	MoveToPlayer();

	if (isMapItemDeath_ == true)
	{
		Player::MainPlayer->GetInventroy()->NewItem<Jazz>();
	}

	switch (ItemState_)
	{
	case ITEM_STATE::INIT:
		Font_->SetPositionItem({ GetPosition() });

		break;

	}
}

void Jazz::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainJazz = this;
	Font_ = Font_;
}

void Jazz::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Font_->NextLevelOn();

}

void Jazz::AddItemCount()
{
	++ItemCount_;
	Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
}

void Jazz::SubItemCount()
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

void Jazz::UpdateOff()
{
	this->Off();
	Font_->Off();
}

void Jazz::UpdateOn()
{
	this->On();
	Font_->On();
}
