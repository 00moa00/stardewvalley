#include "SmallWood2.h"
#include "DropWood.h"

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
	ItemName_ = "SmallWood2";

	ItemType_ = ITEMTYPE::WOOD;

}

void SmallWood2::Update()
{
}

void SmallWood2::DropItemInMap()
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

