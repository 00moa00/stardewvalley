#include "Copper.h"
#include "Player.h"

Copper* Copper::MainCopper = nullptr;
Font* Copper::Font_;
Copper::Copper() 
{
}

Copper::~Copper() 
{
}

void Copper::Start()
{
	ItemSpeed_.x = 1.f;
	ItemSpeed_.y = 5.f;

	ItemRenderer_ = CreateRenderer("springobjects.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::COPPER_ORE));
	ItemRenderer_->CameraEffectOn();

	ItemCollider_ = CreateCollision("Item", { 40.f , 40.f });


	if (Font_ == nullptr)
	{
		Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONT);
	}

	Font_->ChangeWhiteColor();
	Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });


	ItemName_ = "Copper";
	ItemType_ = ITEMTYPE::MINING;

	//핸드 아이템용
	isPossibleHand_ = true;
	FileName_ = "springobjects.bmp";
	FileIndex_ = static_cast<size_t>(ITEM::COPPER_ORE);
}

void Copper::Update()
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
			Inventory::MainInventory->NewItem<Copper>();
		}

		break;
	default:
		break;
	}
}

void Copper::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainCopper = this;
	Font_ = Font_;
}

void Copper::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Font_->NextLevelOn();

}

void Copper::AddItemCount()
{
	++ItemCount_;
	Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
}

void Copper::SubItemCount()
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

void Copper::UpdateOff()
{
	this->Off();
	Font_->Off();
}

void Copper::UpdateOn()
{
	this->On();
	Font_->On();
}
