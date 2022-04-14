#include "MoveBusStop.h"

MoveBusStop::MoveBusStop() 
{
}

MoveBusStop::~MoveBusStop() 
{
}

void MoveBusStop::Start()
{

	ItemRenderer_ = CreateRenderer("block.bmp");

	ItemRenderer_->SetPivotType(RenderPivot::CENTER);
	//SetScale({ 48.f, 48.f });
	ItemCollider_ = CreateCollision("MoveBusStop", { 48, 10 });
	ItemType_ = ITEMTYPE::BLOCK;

}

