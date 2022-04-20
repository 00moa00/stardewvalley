#include "Parsnip_Growing.h"

Parsnip_Growing::Parsnip_Growing() 
{
}

Parsnip_Growing::~Parsnip_Growing() 
{
}

void Parsnip_Growing::Start()
{
	CropRenderer_ = CreateRenderer("crops.bmp");
	CropRenderer_->SetIndex(static_cast<size_t>(CROPS::PARSNIP_SEED));
	CropRenderer_->CameraEffectOn();

	//ItemCollider_ = CreateCollision("Item", { 40, 40 });

	//Name_ = "Parsnip_Growing";
}

void Parsnip_Growing::Update()
{
}

