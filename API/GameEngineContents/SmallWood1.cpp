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

	ItemType_ = ITEMTYPE::ITEM;
	ItemName_ = "SmallWood1";

}

void SmallWood1::Update()
{
}

void SmallWood1::DropItemInMap()
{
	int Count = RandomItemCount.RandomInt(1, 5);
	Items* DropItem;
	for (int i = 0; i < Count; ++i)
	{
		DropItem = CreateDropItemActor<DropWood>();

		float4 Pos;
		Pos.x = RandomItemPosX.RandomFloat(-60.f, 60.f);
		Pos.y = RamdomItemPosY.RandomFloat(-60.f, 60.f);

		DropItem->SetPosition({ this->GetPosition().x + Pos.x, this->GetPosition().y + Pos.y });
		DropItem->SetMoveFlag(true);
	}
}

