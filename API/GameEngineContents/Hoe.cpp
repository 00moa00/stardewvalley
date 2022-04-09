#include "Hoe.h"

Hoe::Hoe() 
{
}

Hoe::~Hoe() 
{
}

void Hoe::Start()
{
	ItemRenderer_ = CreateRenderer("tools.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(TOOL::HOE_IN_INVENTROY));
	ItemRenderer_->CameraEffectOff();

	///ItemRenderer_->SetPivot()
	ItemCollider_ = CreateCollision("Item", { 40, 40 });
	ItemType_ = ITEMTYPE::TOOL;
	
	//Pos = GetPosition();
}

void Hoe::Update()
{

	

}

void Hoe::Render()
{
}
