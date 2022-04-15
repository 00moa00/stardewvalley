#include "Watering_Can.h"

Watering_Can::Watering_Can() 
{
}

Watering_Can::~Watering_Can() 
{
}

void Watering_Can::Start()
{

	ItemRenderer_ = CreateRenderer("tools.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(TOOL::WATER_RIGHT00));
	ItemRenderer_->CameraEffectOff();

	///ItemRenderer_->SetPivot()
	ItemCollider_ = CreateCollision("Item", { 40, 40 });
	ItemType_ = ITEMTYPE::TOOL;
	ToolType_ = TOOLTYPE::WATTERING_CAN;

}

void Watering_Can::Update()
{
}

