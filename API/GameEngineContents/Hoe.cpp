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
	///ItemRenderer_->SetPivot()
	ItemCollider_ = CreateCollision("Item", { 48, 96 });

	//Pos = GetPosition();
}

void Hoe::Update()
{

	

}

void Hoe::Render()
{
}
