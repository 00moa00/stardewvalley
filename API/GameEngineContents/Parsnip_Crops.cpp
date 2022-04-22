#include "Parsnip_Crops.h"

Parsnip_Crops::Parsnip_Crops() 
{
}

Parsnip_Crops::~Parsnip_Crops() 
{
}

void Parsnip_Crops::Start()
{
	CropRenderer_ = CreateRenderer("crops.bmp");
	CropRenderer_->SetIndex(static_cast<size_t>(CROPS::PARSNIP_SEED));
	CropRenderer_->CameraEffectOn();

}

void Parsnip_Crops::Update()
{
}

