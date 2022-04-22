#include "SmallWood1.h"

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

