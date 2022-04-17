#include "MiniWood.h"
#include "Player.h"

MiniWood::MiniWood() 
{
}

MiniWood::~MiniWood() 
{
}

void MiniWood::Start()
{
	ItemSpeed_.x = 1.f;
	ItemSpeed_.y = 5.f;
	Gravity_.y = 0.1f;

	ItemRenderer_ = CreateRenderer("springobjects.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::MINI_WOOD));
	ItemRenderer_->CameraEffectOn();

	MapItemCollider_ = CreateCollision("MapObject", { 20, 20 });
	ItemCollider_ = CreateCollision("Item", { 40, 40 });

	Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONT);
	Font_->ChangeWhiteColor();

	Font_->ChangeNumItem(1);



	ItemType_ = ITEMTYPE::ITEM;

	Name_ = "MiniWood";
}

void MiniWood::Update()
{
	MoveToPlayer();
	if (isDeath_ == true)
	{
		Player* MainPlayer = GetLevel()->FindActor<Player>("MainPlayer");
		MainPlayer->GetInventroy()->NewItem<MiniWood>();
	}


}

//
//void MiniWood::MoveToPlayer()
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
//		//	++Count_;
//		Font_->ChangeNumItem(Count_);
//		//	Font_->SetPositionItem({ GetPosition() });
//
//		ItemState_ = ITEM_STATE::INIT;
//		break;
//	}
//
//	Player* MainPlayer = GetLevel()->FindActor<Player>("MainPlayer");
//
//	if (MoveFlag_ == true)
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
//				MainPlayer->GetInventroy()->NewItem<MiniWood>();
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

