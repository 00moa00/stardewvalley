#include "SmallStone.h"

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

