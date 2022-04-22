#include "SmallWood2.h"

SmallWood2::SmallWood2() 
{
}

SmallWood2::~SmallWood2() 
{
}

void SmallWood2::Start()
{
	ItemRenderer_ = CreateRenderer("Small_Wood2.bmp");

	SetScale({ 35.f, 48.f });
	ItemCollider_ = CreateCollision("MapObject", { 48.f, 48.f });
	ItemType_ = ITEMTYPE::ITEM;
	ItemName_ = "SmallWood2";

}

void SmallWood2::Update()
{
}

