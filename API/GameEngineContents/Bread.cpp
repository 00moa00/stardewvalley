#include "Bread.h"
#include "Inventory.h"

Bread* Bread::MainBread = nullptr;
Font* Bread::Font_ = nullptr;

Bread::Bread() 
{
}

Bread::~Bread() 
{
}

void Bread::Start()
{
	ItemRenderer_ = CreateRenderer("springobjects.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::BREAD));
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
	FileIndex_ = static_cast<size_t>(ITEM::BREAD);

	ItemName_ = "Bread";
	ItemType_ = ITEMTYPE::FOOD;

	SellPrice_ = 120;
}

void Bread::Update()
{
	switch (ItemState_)
	{
	case ITEM_STATE::INIT:

		if (isMove_ == true)
		{
			//Font_->Death();
			PrePosition_ = this->GetPosition();
			ItemState_ = ITEM_STATE::ANIMATION;
		}

		else
		{
			Font_->SetPositionItem({ GetPosition() });

		}

		break;
	case ITEM_STATE::ANIMATION:

		MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 700.0f;
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());
		if (this->GetPosition().y > PrePosition_.y + 30.f)
		{
			this->Death();

		}
		break;

	default:
		break;
	}
}

void Bread::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainBread = this;
	Font_ = Font_;
}

void Bread::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Font_->NextLevelOn();

}

void Bread::AddItemCount()
{
	++ItemCount_;
	Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
}

void Bread::SubItemCount()
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

void Bread::UpdateOff()
{
	this->Off();
	Font_->Off();
}

void Bread::UpdateOn()
{
	this->On();
	Font_->On();
}

void Bread::DropItemInMap()
{
	Items* DropItem = GetLevel()->CreateActor<Bread>(static_cast<int>(PLAYLEVEL::TOP_TOP_OBJECT));
	DropItem->SetPosition({ Player::MainPlayer->GetPosition().x , Player::MainPlayer->GetPosition().y - 100.f });
	DropItem->SetMoveFlag(true);
	DropItem->GetRenderer()->CameraEffectOn();
	DropItem->SetMoveDir({ 0, -200 });
}
