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

	ItemCollider_ = CreateCollision("Item", { 48, 48 });
}

void Weeds::Update()
{
}

void Weeds::Render()
{
}
