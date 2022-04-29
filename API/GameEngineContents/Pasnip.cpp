#include "Pasnip.h"
#include "Inventory.h"

Pasnip* Pasnip::MainPasnip = nullptr;
Font* Pasnip::Font_ = nullptr;

Pasnip::Pasnip() 
{
}

Pasnip::~Pasnip() 
{
}

void Pasnip::Start()
{
	ItemRenderer_ = CreateRenderer("springobjects.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::PARSNIP));
	ItemRenderer_->CameraEffectOff();

	ItemCollider_ = CreateCollision("Item", { 40, 40 });

	if (Font_ == nullptr)
	{
		Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONT);
		Font_->ChangeWhiteColor();
		Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
	}

	ItemName_ = "Pasnip";

	//핸드 아이템용
	isPossibleHand_ = true;
	FileName_ = "springobjects.bmp";
	FileIndex_ = static_cast<size_t>(ITEM::PARSNIP);

	SellPrice_ = 35;
}

void Pasnip::Update()
{

	switch (ItemState_)
	{
	case ITEM_STATE::INIT:
		Font_->SetPositionItem({ GetPosition() });

		if (isMove_ == true)
		{

			PrePosition_ = this->GetPosition();
			ItemState_ = ITEM_STATE::ANIMATION;
		}

		break;
	case ITEM_STATE::ANIMATION:

		MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 700.0f;
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());

		if (this->GetPosition().y > PrePosition_.y)
		{
			ItemState_ = ITEM_STATE::MOVETOPLAYER;

		}

		break;
	case ITEM_STATE::MOVETOPLAYER:

		MoveToPlayer();
		if (isMapItemDeath_ == true)
		{
			Player::MainPlayer->GetInventroy()->NewItem<Pasnip>();
		}

		break;
	default:
		break;
	}



	//MoveToPlayer();

	//if (isMapItemDeath_ == true)
	//{
	//	Inventory::MainInventory->NewItem<Pasnip>();
	//}

	//switch (ItemState_)
	//{
	//case ITEM_STATE::INIT:
	//	Font_->SetPositionItem({ GetPosition() });

	//	break;
	//}
}

void Pasnip::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainPasnip = this;
	Font_ = Font_;
}

void Pasnip::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Font_->NextLevelOn();
}

void Pasnip::AddItemCount()
{
	++ItemCount_;
	Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
}

void Pasnip::SubItemCount()
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

void Pasnip::UpdateOff()
{
	this->Off();
	Font_->Off();
}

void Pasnip::UpdateOn()
{
	this->On();
	Font_->On();
}
