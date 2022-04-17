#include "Items.h"
#include "GameData.h"
#include "Player.h"

Items::Items() :
	ItemRenderer_ (nullptr),
	ItemCollider_ (nullptr),

	MouseHoldItem_ (false),
	InMouse (false),
	isPossibleHand_(false),
	isDeath_(false),
	MoveFlag_(false),
	InBox (true),

	State_(MOVE::Y_UP),
	Normal_(float4::ZERO),
	targetPos_({}),
	TransformPos_({}),
	FileIndex_(0),
	Count_ (1),

	Gravity_({}),
	ItemSpeed_({}),
	ItemPosition_({}),

	Name_ ({""}),
	FilePath_({""}),
	ItemType_ (ITEMTYPE::ITEM),
	ToolType_ (TOOLTYPE::OTHER),
	ItemState_(ITEM_STATE::INIT)
		
{

}

Items::~Items() 
{
}

void Items::Start()
{


}

void Items::Update()
{

//	ItemRenderer_->GetImage()->;

}




bool Items::IsWall(const float4 pos, const float4 scale, float4 dir)
{

	int OtherLeft = pos.ix() - scale.hix();
	int OtherRight = pos.ix() + scale.hix();
	int OtherTop = pos.iy() - scale.hiy();
	int OtherBottom = pos.iy() + scale.hiy();

	//	GameEngineRect DebugRect;


	if (GetRight() < OtherLeft)
	{
		return false;
	}

	if (OtherRight < GetLeft())
	{
		return false;
	}

	if (GetBottom() < OtherTop)
	{
		return false;
	}

	if (OtherBottom < GetTop())
	{
		return false;
	}

	return true;
}

void Items::MoveToPlayer()
{

	switch (ItemState_)
	{
	case ITEM_STATE::INIT:
		Font_->SetPositionItem({ GetPosition() });

		break;

	case ITEM_STATE::ADDITEM:
		//	++Count_;
		Font_->ChangeNumItem(Count_);
		//	Font_->SetPositionItem({ GetPosition() });

		ItemState_ = ITEM_STATE::INIT;
		break;
	}

	Player* MainPlayer = GetLevel()->FindActor<Player>("MainPlayer");

	if (MoveFlag_ == true)
	{

		switch (State_)
		{
		case MOVE::INIT:

			targetPos_ = MainPlayer->GetPosition();
			TransformPos_ = GetPosition();

			Normal_ = (targetPos_ - TransformPos_);
			Normal_.Normal2D();


			ItemPosition_.x += Normal_.x * GameEngineTime::GetDeltaTime() * 4.500f;
			ItemPosition_.y += Normal_.y * GameEngineTime::GetDeltaTime() * 4.500f;

			SetPosition({ GetPosition().x + ItemPosition_.x,  GetPosition().y + ItemPosition_.y });
			Normal_ = float4::ZERO;

			if (playerVSobject())

			{
				MainPlayer->GetInventroy()->NewItem<MiniStone>();

				Death();
			}

			//State_ = MOVE::Y_UP;

			break;

		case MOVE::Y_UP:

			ItemPosition_.x += GameEngineTime::GetDeltaTime() * ItemSpeed_.x;
			ItemPosition_.y += GameEngineTime::GetDeltaTime() * ItemSpeed_.y;

			SetPosition({ GetPosition().x + ItemPosition_.x, GetPosition().y - ItemPosition_.y });

			ItemSpeed_.y -= GameEngineTime::GetDeltaTime() * 30.f;
			//Gravity_.y *= GameEngineTime::GetDeltaTime() * 1.2f;

			if (ItemSpeed_.y < 0)
			{
				State_ = MOVE::Y_DOWN;
			}

			break;
		case MOVE::Y_DOWN:


			ItemPosition_.x += GameEngineTime::GetDeltaTime() * ItemSpeed_.x;
			ItemPosition_.y += GameEngineTime::GetDeltaTime() * ItemSpeed_.y;

			SetPosition({ GetPosition().x + ItemPosition_.x, GetPosition().y + ItemPosition_.y });

			ItemSpeed_.y += GameEngineTime::GetDeltaTime() * 30.f;


			if (ItemSpeed_.y > 5.f)
			{
				State_ = MOVE::INIT;
			}

			break;
		default:
			break;
		}
	}
}
