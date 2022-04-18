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
	ItemRenderer_->SetPivotType(RenderPivot::BOT);

	SetScale({ 48.f, 48.f });

	ItemType_ = ITEMTYPE::ITEM;

	Name_ = "SmallStone";

}

void SmallStone::Update()
{


}

