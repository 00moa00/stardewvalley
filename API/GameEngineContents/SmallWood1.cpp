#include "SmallWood1.h"
#include "DropWood.h"

SmallWood1::SmallWood1() 
{
}

SmallWood1::~SmallWood1() 
{
}

void SmallWood1::Start()
{
	ItemRenderer_ = CreateRenderer("Small_Wood1.bmp");
	ItemCollider_ = CreateCollision("MapObject", { 48.f, 48.f });
	
	SetScale({ 48.f, 48.f });

	ItemName_ = "SmallWood1";

	ItemType_ = ITEMTYPE::WOOD;

}

void SmallWood1::Update()
{
}

void SmallWood1::DropItemInMap()
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

