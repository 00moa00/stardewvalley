#include "Spaghetti.h"
#include "Inventory.h"

Spaghetti* Spaghetti::MainSpaghetti = nullptr;
Font* Spaghetti::Font_ = nullptr;

Spaghetti::Spaghetti() 
{
}

Spaghetti::~Spaghetti() 
{
}

void Spaghetti::Start()
{
	ItemRenderer_ = CreateRenderer("springobjects.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::SPAGHETTI));
	ItemRenderer_->CameraEffectOff();

	ItemCollider_ = CreateCollision("Item", { 40, 40 });

	if (Font_ == nullptr)
	{
		Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONT);
		Font_->ChangeWhiteColor();
		Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
	}

	//핸드 아이템용
	isPossibleHand_ = true;
	FileName_ = "springobjects.bmp";
	FileIndex_ = static_cast<size_t>(ITEM::SPAGHETTI);

	ItemName_ = "Spaghetti";

	SellPrice_ = 35;
}

void Spaghetti::Update()
{
	switch (ItemState_)
	{
	case ITEM_STATE::INIT:
		Font_->SetPositionItem({ GetPosition() });

		break;
	}
}

void Spaghetti::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainSpaghetti = this;
	Font_ = Font_;
}

void Spaghetti::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Font_->NextLevelOn();

}

void Spaghetti::AddItemCount()
{
	++ItemCount_;
	Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
}

void Spaghetti::SubItemCount()
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

void Spaghetti::UpdateOff()
{
	this->Off();
	Font_->Off();
}

void Spaghetti::UpdateOn()
{
	this->On();
	Font_->On();
}
