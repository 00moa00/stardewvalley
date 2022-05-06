#include "Daffodil.h"
#include "Inventory.h"

Daffodil* Daffodil::MainDaffodil = nullptr;
Font* Daffodil::Font_ = nullptr;

Daffodil::Daffodil() 
{
}

Daffodil::~Daffodil() 
{
}

void Daffodil::Start()
{
	ItemRenderer_ = CreateRenderer("springobjects.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::DAFFODIL));
	ItemRenderer_->CameraEffectOff();

	ItemCollider_ = CreateCollision("Item", { 40, 40 });

	if (Font_ == nullptr)
	{
		Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONT);
		Font_->ChangeWhiteColor();
		Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
	}

	ItemType_ = ITEMTYPE::GATHERING;

	//핸드 아이템용
	isPossibleHand_ = true;
	FileName_ = "springobjects.bmp";
	FileIndex_ = static_cast<size_t>(ITEM::DAFFODIL);

	ItemName_ = "Daffodil";

	SellPrice_ = 35;
}

void Daffodil::Update()
{
	switch (ItemState_)
	{
	case ITEM_STATE::INIT:
		Font_->SetPositionItem({ GetPosition() });

		break;
	}
}

void Daffodil::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainDaffodil = this;
	Font_ = Font_;
}

void Daffodil::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Font_->NextLevelOn();
}

void Daffodil::AddItemCount()
{
	++ItemCount_;
	Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
}

void Daffodil::SubItemCount()
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

void Daffodil::UpdateOff()
{
	this->Off();
	Font_->Off();
}

void Daffodil::UpdateOn()
{
	this->On();
	Font_->On();
}
