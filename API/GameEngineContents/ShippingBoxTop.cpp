#include "ShippingBoxTop.h"

ShippingBoxTop::ShippingBoxTop() 
{
}

ShippingBoxTop::~ShippingBoxTop() 
{
}

void ShippingBoxTop::Start()
{
	ItemRenderer_ = CreateRenderer("BoxOpen.bmp");

	ItemRenderer_->CreateAnimation("BoxOpen.bmp", "OPEN", 0, 12, 0.050f, false);
	ItemRenderer_->CreateAnimation("BoxOpen.bmp", "INIT", 0, 0, 0.000f, false);
	ItemRenderer_->CreateAnimation("BoxClose.bmp", "CLOSE", 0, 12, 0.050f, false);

	ItemRenderer_->ChangeAnimation("INIT");

	ItemName_ = "ShippingBoxTop";
}

void ShippingBoxTop::Update()
{
}

void ShippingBoxTop::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
}

void ShippingBoxTop::SetShippingBoxTopAnimationInit()
{
	ItemRenderer_->ChangeAnimation("INIT");
}

void ShippingBoxTop::SetShippingBoxTopAnimationOpen()
{
	ItemRenderer_->ChangeAnimation("OPEN");
}

void ShippingBoxTop::SetShippingBoxTopAnimationClose()
{
	ItemRenderer_->ChangeAnimation("CLOSE");

}
