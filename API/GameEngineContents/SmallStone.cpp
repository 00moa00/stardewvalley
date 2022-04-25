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

	ItemName_ = "SmallStone";

	ItemType_ = ITEMTYPE::STONE;
}

void SmallStone::Update()
{


}

void SmallStone::DropItemInMap()
{
	Items* DropItem = GetLevel()->CreateActor<DropStone>(static_cast<int>(PLAYLEVEL::TOP_TOP_OBJECT));


	DropItem->SetPosition({ this->GetPosition().x + 15.f , this->GetPosition().y });
	DropItem->SetMoveFlag(true);
	DropItem->GetRenderer()->SetScale({ 35.f, 35.f });

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

