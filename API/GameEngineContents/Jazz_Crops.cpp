#include "Jazz_Crops.h"

Jazz_Crops::Jazz_Crops() 
{
}

Jazz_Crops::~Jazz_Crops() 
{
}

void Jazz_Crops::Start()
{
	CropRenderer_ = CreateRenderer("crops.bmp");
	CropRenderer_->SetIndex(static_cast<size_t>(CROPS::JAZZ_SEED));
	CropRenderer_->CameraEffectOn();
}

void Jazz_Crops::Update()
{
}

