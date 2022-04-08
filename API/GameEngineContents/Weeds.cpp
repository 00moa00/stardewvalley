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

	ItemCollider_ = CreateCollision("Item", { 43, 43 });
	ItemType_ = ITEMTYPE::ITEM;
}

void Weeds::Update()
{
}

void Weeds::Render()
{
}
