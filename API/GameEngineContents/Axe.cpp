#include "Axe.h"

Axe::Axe() 
{
}

Axe::~Axe() 
{
}

void Axe::Start()
{
	ItemRenderer_ = CreateRenderer("tools.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(TOOL::AXE_IN_INVENTROY));
	ItemRenderer_->CameraEffectOff();

	///ItemRenderer_->SetPivot()
	ItemCollider_ = CreateCollision("Item", { 40, 40 });
	ItemType_ = ITEMTYPE::TOOL;
	ToolType_ = TOOLTYPE::AXE;

}

void Axe::Update()
{
}

