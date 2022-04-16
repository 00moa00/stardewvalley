#include "Parsnip_Growing.h"

Parsnip_Growing::Parsnip_Growing() 
{
}

Parsnip_Growing::~Parsnip_Growing() 
{
}

void Parsnip_Growing::Start()
{
	ItemRenderer_ = CreateRenderer("crops.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(CROPS::PARSNIP_SEED));
	ItemRenderer_->CameraEffectOn();

	//ItemCollider_ = CreateCollision("Item", { 40, 40 });

	//ItemType_ = ITEMTYPE::TOOL;
	//ToolType_ = TOOLTYPE::AXE;

	Name_ = "Parsnip_Growing";
}

void Parsnip_Growing::Update()
{
}

