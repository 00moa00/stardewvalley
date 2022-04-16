#include "MiniStone.h"
#include "Player.h"
MiniStone::MiniStone() 
{
	State_ = MOVE::Y_UP;
}

MiniStone::~MiniStone() 
{
}

void MiniStone::Start()
{
	ItemSpeed_.x = 1.f;
	ItemSpeed_.y = 5.f;
	Gravity_.y = 0.1f;

	ItemRenderer_ = CreateRenderer("springobjects.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::MINI_STONE));
	ItemRenderer_->CameraEffectOn();

	ItemCollider_ = CreateCollision("MapObject", { 20, 20 });

	//ItemCollider_ = CreateCollision("Item", { 40, 40 });

	ItemType_ = ITEMTYPE::ITEM;

	SetItemName("MiniStone");

}

void MiniStone::Update()
{
	Player* MainPlayer = GetLevel()->FindActor<Player>("MainPlayer");
	float4 targetPos;
	float4 TransformPos;
	float4 Normal = float4::ZERO;

	switch (State_)
	{
	case MOVE::INIT:

		targetPos = MainPlayer->GetPosition();
		TransformPos = GetPosition();

		Normal = (targetPos - TransformPos );
		Normal.Normal2D();


		ItemPosition_.x += Normal.x * GameEngineTime::GetDeltaTime() * 4.500f;
		ItemPosition_.y += Normal.y  * GameEngineTime::GetDeltaTime() * 4.500f;

		SetPosition({ GetPosition().x + ItemPosition_.x,  GetPosition().y + ItemPosition_.y });
		Normal = float4::ZERO;

		if (playerVSobject())

		{
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

