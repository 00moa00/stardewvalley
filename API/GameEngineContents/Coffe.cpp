#include "Coffe.h"
#include "Inventory.h"

Coffe* Coffe::MainCoffe = nullptr;
Font* Coffe::Font_ = nullptr;

Coffe::Coffe() 
{
}

Coffe::~Coffe() 
{
}

void Coffe::Start()
{
	ItemRenderer_ = CreateRenderer("springobjects.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::COFFEE));
	ItemRenderer_->CameraEffectOff();

	ItemCollider_ = CreateCollision("Item", { 40, 40 });

	if (Font_ == nullptr)
	{
		Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONT);
		Font_->ChangeWhiteColor();
		Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
	}

	ItemName_ = "Coffe";

	ObjectType_ = OBJECTTYPE::DRINK;
	DrinkType_ = DRINKTYPE::SPEED_DOWN;

	SellPrice_ = 300;
	AddEnery_ = 3;
	AddHP_ = 1;
	ChangeSpeed_ = 1 * 100;
	ChangeTime_ = 83.0f;

	//핸드 아이템용
	isPossibleHand_ = true;
	FileName_ = "springobjects.bmp";
	FileIndex_ = static_cast<size_t>(ITEM::COFFEE);
}

void Coffe::Update()
{
	switch (ItemState_)
	{
	case ITEM_STATE::INIT:
		Font_->SetPositionItem({ GetPosition() });

		break;
	}
}

void Coffe::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainCoffe = this;
	Font_ = Font_;
}

void Coffe::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Font_->NextLevelOn();
}

void Coffe::AddItemCount()
{
	++ItemCount_;
	Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
}

void Coffe::SubItemCount()
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

void Coffe::UpdateOff()
{
	this->Off();
	Font_->Off();
}

void Coffe::UpdateOn()
{
	this->On();
	Font_->On();
}
