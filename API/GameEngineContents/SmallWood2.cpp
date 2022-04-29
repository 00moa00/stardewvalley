#include "SmallWood2.h"
#include "DropWood.h"
SmallWood2* SmallWood2::MainSmallWood = nullptr;


SmallWood2::SmallWood2() 
{
}

SmallWood2::~SmallWood2() 
{
}

void SmallWood2::Start()
{
	ItemRenderer_ = CreateRenderer("Small_Wood2.bmp");

	ItemCollider_ = CreateCollision("MapObject", { 48.f, 48.f });
	
	SetScale({ 48.f, 48.f });

	ItemName_ = "SmallWood2";

	ItemType_ = ITEMTYPE::WOOD;

}

void SmallWood2::Update()
{
}

void SmallWood2::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainSmallWood = this;
}

void SmallWood2::DropItemInMap()
{
	Items* DropItem = GetLevel()->CreateActor<DropWood>(static_cast<int>(PLAYLEVEL::TOP_TOP_OBJECT));

	DropItem->SetPosition({ this->GetPosition().x + 15.f , this->GetPosition().y });
	DropItem->SetMoveFlag(true);
	DropItem->GetRenderer()->SetScale({ 40.f, 40.f });

	GameEngineRandom RandomDir;
	int RamdomDir = RandomDir.RandomInt(1, 2);


	if (RamdomDir == 1)
	{
		DropItem->SetMoveDir({ 0, -120 });

	}
	if (RamdomDir == 2)
	{
		DropItem->SetMoveDir({ 0, -120 });

	}
}

