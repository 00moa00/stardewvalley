#include "Tulip_Crops.h"

Tulip_Crops::Tulip_Crops() 
{
}

Tulip_Crops::~Tulip_Crops() 
{
}

void Tulip_Crops::Start()
{
	CropRenderer_ = CreateRenderer("crops.bmp");
	CropRenderer_-> SetIndex(static_cast<size_t>(CROPS::TULIP_SEED));
	CropRenderer_-> CameraEffectOn();
}

void Tulip_Crops::Update()
{
}

