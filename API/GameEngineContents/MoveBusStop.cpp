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

	ItemCollider_ = CreateCollision("MoveBusStop", { 48, 48 });

	ItemType_ = ITEMTYPE::FALG;

}

