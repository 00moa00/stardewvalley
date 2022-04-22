#include "SmallStone.h"
#include "DropStone.h"

SmallStone::SmallStone() 
{
}

SmallStone::~SmallStone() 
{
}

void SmallStone::Start()
{

	ItemRenderer_ = CreateRenderer("Small_Stone.bmp");
	ItemCollider_ = CreateCollision("MapObject", { 48.f, 48.f });

	SetScale({ 48.f, 48.f });

	ItemType_ = ITEMTYPE::ITEM;

	ItemName_ = "SmallStone";

}

void SmallStone::Update()
{


}

void SmallStone::DropItemInMap()
{
	int Count = RandomItemCount.RandomInt(1, 5);
	Items* DropItem;
	for (int i = 0; i < Count; ++i)
	{
		DropItem = CreateDropItemActor<DropStone>();

		float4 Pos;
		Pos.x = RandomItemPosX.RandomFloat(-60.f, 60.f);
		Pos.y = RamdomItemPosY.RandomFloat(-60.f, 60.f);

		DropItem->SetPosition({ this->GetPosition().x + Pos.x, this->GetPosition().y + Pos.y });
		DropItem->SetMoveFlag(true);
	}

}

