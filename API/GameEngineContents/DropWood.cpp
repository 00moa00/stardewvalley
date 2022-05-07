#include "DropWood.h"
#include "Player.h"

DropWood* DropWood::MainDropWood = nullptr;
Font* DropWood::Font_ = nullptr;

DropWood::DropWood() 
{
}

DropWood::~DropWood() 
{
}

void DropWood::Start()
{


	ItemRenderer_ = CreateRenderer("springobjects.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::MINI_WOOD));
	ItemRenderer_->CameraEffectOn();

	ItemCollider_ = CreateCollision("Item", { 40.f , 40.f });

	if (Font_ == nullptr)
	{
		Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONT);
		Font_->ChangeWhiteColor();
		Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
	}

	ItemType_ = ITEMTYPE::OTHER;
	SellPrice_ = 10;

	//핸드 아이템용
	isPossibleHand_ = true;
	FileName_ = "springobjects.bmp";
	FileIndex_ = static_cast<size_t>(ITEM::MINI_WOOD);


}

void DropWood::Update()
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

		if (this->GetPosition().y > PrePosition_.y )
		{
			ItemState_ = ITEM_STATE::MOVETOPLAYER;

		}

		break;
	case ITEM_STATE::MOVETOPLAYER:

		MoveToPlayer();
		if (isMapItemDeath_ == true)
		{
			Player:: MainPlayer->GetInventroy()->NewItem<DropWood>();
		}

		break;
	default:
		break;
	}


}

void DropWood::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainDropWood = this;
	Font_ = Font_;

}

void DropWood::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Font_->NextLevelOn();

}

void DropWood::AddItemCount()
{
	++ItemCount_;
	Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
}

void DropWood::SubItemCount()
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

void DropWood::UpdateOff()
{
	this->Off();
	Font_->Off();
}

void DropWood::UpdateOn()
{
	this->On();
	Font_->On();
}

//
//void DropWood::MoveToPlayer()
//{
//
//	switch (ItemState_)
//	{
//	case ITEM_STATE::INIT:
//		Font_->SetPositionItem({ GetPosition() });
//
//		break;
//
//	case ITEM_STATE::ADDITEM:
//		//	++ItemCount_;
//		Font_->ChangeNumItem(ItemCount_);
//		//	Font_->SetPositionItem({ GetPosition() });
//
//		ItemState_ = ITEM_STATE::INIT;
//		break;
//	}
//
//	Player* MainPlayer = GetLevel()->FindActor<Player>("MainPlayer");
//
//	if (isEvent_ == true)
//	{
//
//		switch (State_)
//		{
//		case MOVE::INIT:
//
//			targetPos_ = MainPlayer->GetPosition();
//			TransformPos_ = GetPosition();
//
//			Normal_ = (targetPos_ - TransformPos_);
//			Normal_.Normal2D();
//
//
//			ItemPosition_.x += Normal_.x * GameEngineTime::GetDeltaTime() * 4.500f;
//			ItemPosition_.y += Normal_.y * GameEngineTime::GetDeltaTime() * 4.500f;
//
//			SetPosition({ GetPosition().x + ItemPosition_.x,  GetPosition().y + ItemPosition_.y });
//			Normal_ = float4::ZERO;
//
//			if (playerVSobject())
//
//			{
//				MainPlayer->GetInventroy()->NewItem<DropWood>();
//
//				Death();
//			}
//
//			//State_ = MOVE::Y_UP;
//
//			break;
//
//		case MOVE::Y_UP:
//
//			ItemPosition_.x += GameEngineTime::GetDeltaTime() * ItemSpeed_.x;
//			ItemPosition_.y += GameEngineTime::GetDeltaTime() * ItemSpeed_.y;
//
//			SetPosition({ GetPosition().x + ItemPosition_.x, GetPosition().y - ItemPosition_.y });
//
//			ItemSpeed_.y -= GameEngineTime::GetDeltaTime() * 30.f;
//			//Gravity_.y *= GameEngineTime::GetDeltaTime() * 1.2f;
//
//			if (ItemSpeed_.y < 0)
//			{
//				State_ = MOVE::Y_DOWN;
//			}
//
//			break;
//		case MOVE::Y_DOWN:
//
//
//			ItemPosition_.x += GameEngineTime::GetDeltaTime() * ItemSpeed_.x;
//			ItemPosition_.y += GameEngineTime::GetDeltaTime() * ItemSpeed_.y;
//
//			SetPosition({ GetPosition().x + ItemPosition_.x, GetPosition().y + ItemPosition_.y });
//
//			ItemSpeed_.y += GameEngineTime::GetDeltaTime() * 30.f;
//
//
//			if (ItemSpeed_.y > 5.f)
//			{
//				State_ = MOVE::INIT;
//			}
//
//			break;
//		default:
//			break;
//		}
//	}
//}

