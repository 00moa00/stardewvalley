#include "Weeds.h"

Weeds::Weeds() 
{
}

Weeds::~Weeds() 
{
}

void Weeds::Start()
{
	ItemRenderer_ = CreateRenderer("springobjects.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::WEEDS));
	ItemRenderer_->CameraEffectOff();

	ItemCollider_ = CreateCollision("Item", { 40, 40 });
}

void Weeds::Update()
{
}

void Weeds::Render()
{
}
