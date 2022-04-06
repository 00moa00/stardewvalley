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
	ItemRenderer_->SetIndex(static_cast<size_t>(TOOL::HOE_INIT));

	ItemCollider_ = CreateCollision("Item", { 48, 96 });
}

void Hoe::Update()
{
}

void Hoe::Render()
{
}
