#include "Bread.h"
#include "Inventory.h"

Bread* Bread::MainBread = nullptr;
Font* Bread::Font_ = nullptr;
ItemDataBox* Bread::MainItemDataBox = nullptr;

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

	ItemName_ = "Bread";
	ObjectType_ = OBJECTTYPE::FOOD;

	SellPrice_ = 120;
	AddEnery_ = 50;
	AddHP_ = 22;

	ItemType_ = ITEMTYPE::ETC;

	if (Font_ == nullptr)
	{
		Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONT);
		Font_->ChangeWhiteColor();
		Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
	}

	if (MainItemDataBox == nullptr)
	{
		MainItemDataBox = GetLevel()->CreateActor<ItemDataBox>(static_cast<int>(PLAYLEVEL::DIALOGUEBOX));
		MainItemDataBox->SetData(ItemName_, " ", this->GetPosition());
	}

	//핸드 아이템용
	isPossibleHand_ = true;
	FileName_ = "springobjects.bmp";
	FileIndex_ = static_cast<size_t>(ITEM::BREAD);
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
			if (MouseOver() && InMouse == false)
			{
				MainItemDataBox->ItemDataBoxOn();
				MainItemDataBox->SetData(ItemName_, "50 Energy /22 Health", this->GetPosition());
			}
			else
			{
				MainItemDataBox->ItemDataBoxOff();
			}
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
	MainItemDataBox = MainItemDataBox;

}

void Bread::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Font_->NextLevelOn();
	MainItemDataBox->NextLevelOn();
	MainItemDataBox->FontNextLevelOn();
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
